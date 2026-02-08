package tile;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class RandomDungeonMap {

    private static final int VOID = 0;
    private static final int DIRT = 1;
    private static final int FLOAT_BEDROCK = 2;
    private static final int MIN_GAP = 7;

    public static class Result {
        public int[][] mapTiles;
        public int[][] mapFloatTiles;
        public int startX;
        public int startY;
        public int endX;
        public int endY;
        public List<RoomInfo> rooms;
    }

    public static class RoomInfo {
        public int x, y, w, h;
        public int centerX;
        public int centerY;
        public int parentIndex;
    }

    private static class Room {
        int x, y, w, h;
        int centerX, centerY;
        int parentIndex = -1;
        int centerX() { return x + w / 2; }
        int centerY() { return y + h / 2; }
    }

    public static Result generate(int cols, int rows, int roomCount, Random rng) {
        int[][] map = new int[cols][rows];
        int[][] floatMap = new int[cols][rows];
        for (int x = 0; x < cols; x++) {
            for (int y = 0; y < rows; y++) {
                map[x][y] = VOID;
                floatMap[x][y] = 0;
            }
        }

        List<Room> rooms = new ArrayList<>();
        double bestDistSq = -1;

        for (int attempt = 0; attempt < 40; attempt++) {
            List<Room> candidate = buildChain(cols, rows, roomCount, rng);
            if (candidate.size() != roomCount) continue;

            Room start = candidate.get(0);
            Room end = candidate.get(candidate.size() - 1);
            double dx = end.centerX - start.centerX;
            double dy = end.centerY - start.centerY;
            double distSq = dx * dx + dy * dy;
            if (distSq > bestDistSq) {
                bestDistSq = distSq;
                rooms = candidate;
            }
        }

        if (rooms.size() < 2) {
            Room r = new Room();
            r.w = 10; r.h = 10;
            r.centerX = cols / 2;
            r.centerY = rows / 2;
            r.x = Math.max(2, r.centerX - r.w / 2);
            r.y = Math.max(2, r.centerY - r.h / 2);
            rooms.clear();
            rooms.add(r);
        }

        // carve rooms
        for (Room r : rooms) {
            carveRoom(map, r);
        }

        // carve corridors based on parent links
        for (int i = 1; i < rooms.size(); i++) {
            Room r = rooms.get(i);
            if (r.parentIndex >= 0 && r.parentIndex < rooms.size()) {
                Room p = rooms.get(r.parentIndex);
                carveCorridorStraight(map, p.centerX, p.centerY, r.centerX, r.centerY);
            }
        }

        addBedrockBorder(map, floatMap);

        Result result = new Result();
        result.mapTiles = map;
        result.mapFloatTiles = floatMap;

        Room start = rooms.get(0);
        Room end = rooms.get(rooms.size() - 1);
        result.startX = start.centerX;
        result.startY = start.centerY;
        result.endX = end.centerX;
        result.endY = end.centerY;

        result.rooms = new ArrayList<>();
        for (Room r : rooms) {
            RoomInfo info = new RoomInfo();
            info.x = r.x; info.y = r.y; info.w = r.w; info.h = r.h;
            info.centerX = r.centerX;
            info.centerY = r.centerY;
            info.parentIndex = r.parentIndex;
            result.rooms.add(info);
        }

        return result;
    }

    private static Room createFirstRoom(int cols, int rows, Random rng){
        Room r = new Room();
        r.w = 10;
        r.h = 10;
        r.centerX = 2 + rng.nextInt(Math.max(1, cols - 4));
        r.centerY = 2 + rng.nextInt(Math.max(1, rows - 4));
        r.x = r.centerX - r.w / 2;
        r.y = r.centerY - r.h / 2;
        clampRoomToBounds(r, cols, rows);
        return r;
    }

    private static Room createEndRoom(int cols, int rows, Random rng){
        Room r = new Room();
        r.w = 10;
        r.h = 10;
        r.centerX = 2 + rng.nextInt(Math.max(1, cols - 4));
        r.centerY = 2 + rng.nextInt(Math.max(1, rows - 4));
        r.x = r.centerX - r.w / 2;
        r.y = r.centerY - r.h / 2;
        clampRoomToBounds(r, cols, rows);
        return r;
    }

    private static Room createRoomNextTo(Room parent, int cols, int rows, Random rng, List<Room> rooms){
        for (int attempt = 0; attempt < 40; attempt++) {
            Room r = new Room();
            r.w = randomEven(14, 20, rng);
            r.h = randomEvenWithMaxDiff(14, 24, r.w, 6, rng);

            int dir = rng.nextInt(4);
            if (dir == 0 || dir == 1) {
                // horizontal placement
                int minDist = parent.w / 2 + r.w / 2 + MIN_GAP;
                int extra = rng.nextInt(6); // 0-5 extra spacing
                int dist = minDist + extra;
                r.centerY = parent.centerY;
                r.centerX = parent.centerX + (dir == 0 ? -dist : dist);
            } else {
                // vertical placement
                int minDist = parent.h / 2 + r.h / 2 + MIN_GAP;
                int extra = rng.nextInt(6); // 0-5 extra spacing
                int dist = minDist + extra;
                r.centerX = parent.centerX;
                r.centerY = parent.centerY + (dir == 2 ? -dist : dist);
            }

            r.x = r.centerX - r.w / 2;
            r.y = r.centerY - r.h / 2;

            if (!fitsBounds(r, cols, rows)) continue;
            if (overlapsAny(r, rooms)) continue;

            r.parentIndex = rooms.indexOf(parent);
            return r;
        }
        return null;
    }

    private static List<Room> buildChain(int cols, int rows, int roomCount, Random rng){
        List<Room> rooms = new ArrayList<>();
        Room start = createFirstRoom(cols, rows, rng);
        rooms.add(start);

        int attempts = 0;
        while (rooms.size() < roomCount - 1 && attempts < roomCount * 800) {
            attempts++;
            Room parent = rooms.get(rooms.size() - 1);
            Room next = createRoomNextTo(parent, cols, rows, rng, rooms);
            if (next != null) {
                rooms.add(next);
            }
        }

        if (rooms.size() < roomCount - 1) {
            return rooms;
        }

        // force end room as 10x10 connected to last room
        Room last = rooms.get(rooms.size() - 1);
        Room end = createEndRoom(cols, rows, rng);
        end.parentIndex = rooms.indexOf(last);

        // align end with last room axis and min gap
        for (int attempt = 0; attempt < 80; attempt++) {
            int dir = rng.nextInt(4);
            if (dir == 0 || dir == 1) {
                int minDist = last.w / 2 + end.w / 2 + MIN_GAP;
                int dist = minDist + rng.nextInt(6);
                end.centerY = last.centerY;
                end.centerX = last.centerX + (dir == 0 ? -dist : dist);
            } else {
                int minDist = last.h / 2 + end.h / 2 + MIN_GAP;
                int dist = minDist + rng.nextInt(6);
                end.centerX = last.centerX;
                end.centerY = last.centerY + (dir == 2 ? -dist : dist);
            }

            end.x = end.centerX - end.w / 2;
            end.y = end.centerY - end.h / 2;

            if (!fitsBounds(end, cols, rows)) continue;
            if (overlapsAny(end, rooms)) continue;
            rooms.add(end);
            if (rooms.size() == roomCount) return rooms;
        }

        // end placement failed
        return new ArrayList<>();
    }

    private static int randomEven(int min, int max, Random rng){
        int minEven = (min % 2 == 0) ? min : min + 1;
        int maxEven = (max % 2 == 0) ? max : max - 1;
        if (maxEven < minEven) return minEven;
        int count = ((maxEven - minEven) / 2) + 1;
        return minEven + 2 * rng.nextInt(count);
    }

    private static int randomEvenWithMaxDiff(int min, int max, int base, int maxDiff, Random rng){
        int minEven = (min % 2 == 0) ? min : min + 1;
        int maxEven = (max % 2 == 0) ? max : max - 1;
        int low = Math.max(minEven, base - maxDiff);
        int high = Math.min(maxEven, base + maxDiff);
        if (low % 2 != 0) low++;
        if (high % 2 != 0) high--;
        if (high < low) return base;
        int count = ((high - low) / 2) + 1;
        return low + 2 * rng.nextInt(count);
    }

    private static boolean overlapsAny(Room r, List<Room> rooms){
        for (Room other : rooms) {
            if (intersects(r, other, MIN_GAP)) return true;
        }
        return false;
    }

    private static boolean fitsBounds(Room r, int cols, int rows){
        return r.x >= 1 && r.y >= 1 && r.x + r.w < cols - 1 && r.y + r.h < rows - 1;
    }

    private static void clampRoomToBounds(Room r, int cols, int rows){
        if (r.x < 1) r.x = 1;
        if (r.y < 1) r.y = 1;
        if (r.x + r.w >= cols - 1) r.x = cols - 2 - r.w;
        if (r.y + r.h >= rows - 1) r.y = rows - 2 - r.h;
        r.centerX = r.x + r.w / 2;
        r.centerY = r.y + r.h / 2;
    }

    private static boolean intersects(Room a, Room b, int padding) {
        int ax1 = a.x - padding;
        int ay1 = a.y - padding;
        int ax2 = a.x + a.w + padding;
        int ay2 = a.y + a.h + padding;
        int bx1 = b.x;
        int by1 = b.y;
        int bx2 = b.x + b.w;
        int by2 = b.y + b.h;
        return ax1 < bx2 && ax2 > bx1 && ay1 < by2 && ay2 > by1;
    }

    private static void carveRoom(int[][] map, Room r) {
        for (int x = r.x; x < r.x + r.w; x++) {
            for (int y = r.y; y < r.y + r.h; y++) {
                map[x][y] = DIRT;
            }
        }
    }

    private static void carveCorridorStraight(int[][] map, int x1, int y1, int x2, int y2) {
        if (x1 != x2 && y1 != y2) return; // must be straight

        int length = (x1 == x2) ? Math.abs(y2 - y1) : Math.abs(x2 - x1);
        if (length < 7) return; // corridor length must be at least 7

        if (x1 == x2) {
            // vertical corridor, width 2 centered on x1 (columns x1-1 and x1)
            int start = Math.min(y1, y2);
            int end = Math.max(y1, y2);
            for (int y = start; y <= end; y++) {
                carveWidth2Vertical(map, x1, y);
            }
        } else {
            // horizontal corridor, width 2 centered on y1 (rows y1-1 and y1)
            int start = Math.min(x1, x2);
            int end = Math.max(x1, x2);
            for (int x = start; x <= end; x++) {
                carveWidth2Horizontal(map, x, y1);
            }
        }
    }

    private static void carveWidth2Vertical(int[][] map, int centerX, int y) {
        int xA = centerX - 1;
        int xB = centerX;
        if (y < 0 || y >= map[0].length) return;
        if (xA >= 0 && xA < map.length) map[xA][y] = DIRT;
        if (xB >= 0 && xB < map.length) map[xB][y] = DIRT;
    }

    private static void carveWidth2Horizontal(int[][] map, int x, int centerY) {
        int yA = centerY - 1;
        int yB = centerY;
        if (x < 0 || x >= map.length) return;
        if (yA >= 0 && yA < map[0].length) map[x][yA] = DIRT;
        if (yB >= 0 && yB < map[0].length) map[x][yB] = DIRT;
    }

    private static void addBedrockBorder(int[][] map, int[][] floatMap){
        int cols = map.length;
        int rows = map[0].length;

        for (int x = 0; x < cols; x++){
            for (int y = 0; y < rows; y++){
                if (map[x][y] != DIRT) continue;
                for (int dx = -1; dx <= 1; dx++){
                    for (int dy = -1; dy <= 1; dy++){
                        int nx = x + dx;
                        int ny = y + dy;
                        if (nx < 0 || ny < 0 || nx >= cols || ny >= rows) continue;
                        if (map[nx][ny] == VOID && floatMap[nx][ny] == 0) {
                            floatMap[nx][ny] = FLOAT_BEDROCK;
                        }
                    }
                }
            }
        }
    }
}
