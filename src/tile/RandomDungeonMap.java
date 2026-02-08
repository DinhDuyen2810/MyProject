package tile;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class RandomDungeonMap {

    public static class Result {
        public int[][] mapTiles;
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
    }

    private static class Room {
        int x, y, w, h;
        int centerX() { return x + w / 2; }
        int centerY() { return y + h / 2; }
    }

    public static Result generate(int cols, int rows, int roomCount, Random rng) {
        int[][] map = new int[cols][rows];
        // default VOID = 0
        for (int x = 0; x < cols; x++) {
            for (int y = 0; y < rows; y++) {
                map[x][y] = 0;
            }
        }

        List<Room> rooms = new ArrayList<>();

        // Grid settings to align centers so that adjacent rooms share same x or y
        final int step = 16; // distance between room centers (even)
        final int minCenterX = step / 2;
        final int minCenterY = step / 2;
        final int maxCenterX = cols - step / 2 - 1;
        final int maxCenterY = rows - step / 2 - 1;
        final int gridMaxX = Math.max(0, (maxCenterX - minCenterX) / step);
        final int gridMaxY = Math.max(0, (maxCenterY - minCenterY) / step);

        class Pos { int gx, gy; Pos(int gx, int gy){ this.gx=gx; this.gy=gy; } }
        java.util.Map<String, Room> placed = new java.util.HashMap<>();
        java.util.List<Pos> placedPos = new java.util.ArrayList<>();

        // pick start position
        int startGX = rng.nextInt(gridMaxX + 1);
        int startGY = rng.nextInt(gridMaxY + 1);
        Room startRoom = createRoomAt(map, startGX, startGY, minCenterX, minCenterY, step, cols, rows, rng, rooms);
        if (startRoom == null) {
            Room fallback = new Room();
            fallback.w = 14; fallback.h = 14;
            fallback.x = Math.max(2, cols / 2 - fallback.w / 2);
            fallback.y = Math.max(2, rows / 2 - fallback.h / 2);
            rooms.clear();
            rooms.add(fallback);
            carveRoom(map, fallback);
            startRoom = fallback;
        }
        placed.put(key(startGX, startGY), startRoom);
        placedPos.add(new Pos(startGX, startGY));

        int attempts = 0;
        while (rooms.size() < roomCount && attempts < roomCount * 400) {
            attempts++;

            Pos basePos = placedPos.get(rng.nextInt(placedPos.size()));
            int dir = rng.nextInt(4);
            int nx = basePos.gx + (dir == 1 ? 1 : dir == 0 ? -1 : 0);
            int ny = basePos.gy + (dir == 3 ? 1 : dir == 2 ? -1 : 0);

            if (nx < 0 || ny < 0 || nx > gridMaxX || ny > gridMaxY) continue;
            if (placed.containsKey(key(nx, ny))) continue;

            Room newRoom = createRoomAt(map, nx, ny, minCenterX, minCenterY, step, cols, rows, rng, rooms);
            if (newRoom == null) continue;

            placed.put(key(nx, ny), newRoom);
            placedPos.add(new Pos(nx, ny));

            Room parent = placed.get(key(basePos.gx, basePos.gy));
            carveCorridorStraight(map, parent.centerX(), parent.centerY(), newRoom.centerX(), newRoom.centerY());
        }

        if (rooms.size() < 2) {
            Room r = new Room();
            r.w = 14; r.h = 14;
            r.x = Math.max(2, cols / 2 - r.w / 2);
            r.y = Math.max(2, rows / 2 - r.h / 2);
            rooms.clear();
            rooms.add(r);
            carveRoom(map, r);
        }

        Result result = new Result();
        result.mapTiles = map;

        Room start = rooms.get(0);
        Room end = rooms.get(rooms.size() - 1);
        result.startX = start.centerX();
        result.startY = start.centerY();
        result.endX = end.centerX();
        result.endY = end.centerY();

        result.rooms = new ArrayList<>();
        for (Room r : rooms) {
            RoomInfo info = new RoomInfo();
            info.x = r.x; info.y = r.y; info.w = r.w; info.h = r.h;
            info.centerX = r.centerX();
            info.centerY = r.centerY();
            result.rooms.add(info);
        }

        return result;
    }

    private static String key(int gx, int gy){
        return gx + "," + gy;
    }

    private static Room createRoomAt(int[][] map, int gx, int gy, int minCenterX, int minCenterY,
                                     int step, int cols, int rows, Random rng, List<Room> rooms){
        int centerX = minCenterX + gx * step;
        int centerY = minCenterY + gy * step;

        for (int attempt = 0; attempt < 8; attempt++) {
            int w = 14 + 2 * rng.nextInt(4); // 14,16,18,20
            int h = 14 + 2 * rng.nextInt(4); // 14,16,18,20
            int x = centerX - w / 2;
            int y = centerY - h / 2;

            if (x < 1 || y < 1 || x + w >= cols - 1 || y + h >= rows - 1) continue;

            Room r = new Room();
            r.x = x; r.y = y; r.w = w; r.h = h;

            boolean overlaps = false;
            for (Room other : rooms) {
                if (intersects(r, other, 2)) {
                    overlaps = true;
                    break;
                }
            }
            if (!overlaps) {
                rooms.add(r);
                carveRoom(map, r);
                return r;
            }
        }
        return null;
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
                map[x][y] = 1; // DIRT
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
        if (xA >= 0 && xA < map.length) map[xA][y] = 1;
        if (xB >= 0 && xB < map.length) map[xB][y] = 1;
    }

    private static void carveWidth2Horizontal(int[][] map, int x, int centerY) {
        int yA = centerY - 1;
        int yB = centerY;
        if (x < 0 || x >= map.length) return;
        if (yA >= 0 && yA < map[0].length) map[x][yA] = 1;
        if (yB >= 0 && yB < map[0].length) map[x][yB] = 1;
    }
}
