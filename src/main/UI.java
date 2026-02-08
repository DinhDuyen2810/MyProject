package main;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;


public class UI {
    GamePanel gp;
    Font arial_20;
    BufferedImage diamondImage;
    public boolean messageOn = false;
    public String message = "";
    int counter = 0;

    public UI(GamePanel gp){
        this.gp = gp;
        arial_20 = new Font("Arial", Font.PLAIN, 20);
        // no diamond UI image anymore
        diamondImage = null;
    }

    public void showMessage(String message){
        this.message = message;
        messageOn = true;
    }

    public void draw(Graphics2D g2){
        g2.setFont(arial_20);
        g2.setColor(Color.WHITE);
        // Show debug info only when F3 toggled
        if (gp.keyH.showDebug) {
            // first coordinates then FPS
            g2.drawString("x: " + (gp.player.worldX + gp.player.solidPoint.x) + "  y: "
                                + (gp.player.worldY + gp.player.solidPoint.y), 10, 20);
            g2.drawString("FPS: " + gp.currentFPS, 10, 40);
        }

        drawMiniMap(g2);

        // MESSAGE
        if(messageOn){
            g2.drawString(message, 10, 100);
            counter++;

            if(counter > gp.FPS){
                messageOn = false;
                counter = 0;
            }
        }
    }

    private void drawMiniMap(Graphics2D g2){
        tile.RandomDungeonMap.Result dungeon = gp.getDungeonMap();
        if (dungeon == null || dungeon.rooms == null || dungeon.rooms.isEmpty()) return;

        int margin = 10;
        int maxSize = 110;
        int originX = gp.screenWidth - maxSize - margin;
        int originY = margin;

        // background panel
        g2.setColor(new Color(0, 0, 0, 160));
        g2.fillRect(originX - 2, originY - 2, maxSize + 4, maxSize + 4);

        int playerTileX = (int)Math.round(gp.player.worldX / gp.tileSize);
        int playerTileY = (int)Math.round(gp.player.worldY / gp.tileSize);
        boolean[] visited = gp.getDungeonVisited();

        int playerRoomIndex = -1;
        int doorRoomIndex = -1;

        for (int i = 0; i < dungeon.rooms.size(); i++){
            tile.RandomDungeonMap.RoomInfo r = dungeon.rooms.get(i);
            if (playerTileX >= r.x && playerTileX < r.x + r.w &&
                playerTileY >= r.y && playerTileY < r.y + r.h) {
                playerRoomIndex = i;
            }
            if (dungeon.endX >= r.x && dungeon.endX < r.x + r.w &&
                dungeon.endY >= r.y && dungeon.endY < r.y + r.h) {
                doorRoomIndex = i;
            }
        }

        // build adjacency from parent links
        int n = dungeon.rooms.size();
        java.util.List<java.util.List<Integer>> neighbors = new java.util.ArrayList<>();
        for (int i = 0; i < n; i++) neighbors.add(new java.util.ArrayList<>());
        for (int i = 0; i < n; i++){
            tile.RandomDungeonMap.RoomInfo r = dungeon.rooms.get(i);
            if (r.parentIndex >= 0 && r.parentIndex < n){
                neighbors.get(i).add(r.parentIndex);
                neighbors.get(r.parentIndex).add(i);
            }
        }

        boolean[] visible = new boolean[n];
        if (visited != null && visited.length == n){
            for (int i = 0; i < n; i++){
                if (visited[i]) {
                    visible[i] = true;
                    for (int nb : neighbors.get(i)) visible[nb] = true;
                }
            }
        }

        boolean endVisible = doorRoomIndex >= 0 && doorRoomIndex < n && visible[doorRoomIndex];

        // build abstract grid positions with equal spacing
        int[] gridX = new int[n];
        int[] gridY = new int[n];
        boolean[] placed = new boolean[n];
        java.util.Set<String> occupied = new java.util.HashSet<>();

        gridX[0] = 0; gridY[0] = 0; placed[0] = true;
        occupied.add("0,0");

        for (int i = 1; i < n; i++){
            tile.RandomDungeonMap.RoomInfo r = dungeon.rooms.get(i);
            int pIndex = r.parentIndex;
            if (pIndex < 0 || pIndex >= n || !placed[pIndex]) {
                pIndex = 0;
            }
            int px = gridX[pIndex];
            int py = gridY[pIndex];

            tile.RandomDungeonMap.RoomInfo p = dungeon.rooms.get(pIndex);
            int dx = 0;
            int dy = 0;
            if (r.centerX == p.centerX) {
                dy = Integer.compare(r.centerY, p.centerY);
                if (dy == 0) dy = 1;
            } else {
                dx = Integer.compare(r.centerX, p.centerX);
                if (dx == 0) dx = 1;
            }

            int nx = px + dx;
            int ny = py + dy;
            if (occupied.contains(nx + "," + ny)) {
                boolean found = false;
                // try extending along same axis
                for (int step = 2; step <= 6; step++){
                    int tx = px + dx * step;
                    int ty = py + dy * step;
                    if (!occupied.contains(tx + "," + ty)) {
                        nx = tx; ny = ty; found = true; break;
                    }
                }
                if (!found) {
                    // fallback: try orthogonal neighbors around parent
                    int[][] candidates = new int[][]{
                        {px + 1, py}, {px - 1, py}, {px, py + 1}, {px, py - 1}
                    };
                    for (int[] c : candidates){
                        if (!occupied.contains(c[0] + "," + c[1])) {
                            nx = c[0]; ny = c[1]; found = true; break;
                        }
                    }
                }
            }

            gridX[i] = nx;
            gridY[i] = ny;
            placed[i] = true;
            occupied.add(nx + "," + ny);
        }

        int minGX = gridX[0], maxGX = gridX[0];
        int minGY = gridY[0], maxGY = gridY[0];
        for (int i = 0; i < n; i++){
            minGX = Math.min(minGX, gridX[i]);
            maxGX = Math.max(maxGX, gridX[i]);
            minGY = Math.min(minGY, gridY[i]);
            maxGY = Math.max(maxGY, gridY[i]);
        }

        int gridW = maxGX - minGX + 1;
        int gridH = maxGY - minGY + 1;
        int spacing = Math.max(10, Math.min(maxSize / Math.max(1, gridW), maxSize / Math.max(1, gridH))) / 2;
        int mapW = gridW * spacing;
        int mapH = gridH * spacing;
        int offsetX = originX + (maxSize - mapW) / 2;
        int offsetY = originY + (maxSize - mapH) / 2;

        // draw corridors first
        g2.setColor(new Color(110, 110, 110));
        for (int i = 0; i < n; i++){
            tile.RandomDungeonMap.RoomInfo r = dungeon.rooms.get(i);
            if (r.parentIndex >= 0 && r.parentIndex < n){
                if (!visible[i] || !visible[r.parentIndex]) continue;
                int x1 = offsetX + (gridX[i] - minGX) * spacing;
                int y1 = offsetY + (gridY[i] - minGY) * spacing;
                int x2 = offsetX + (gridX[r.parentIndex] - minGX) * spacing;
                int y2 = offsetY + (gridY[r.parentIndex] - minGY) * spacing;
                drawLine2px(g2, x1, y1, x2, y2);
            }
        }

        // draw rooms as equal squares
        int roomSize = 6;
        for (int i = 0; i < n; i++){
            if (!visible[i]) continue;
            int cx = offsetX + (gridX[i] - minGX) * spacing;
            int cy = offsetY + (gridY[i] - minGY) * spacing;
            int x = cx - roomSize / 2;
            int y = cy - roomSize / 2;

            if (i == doorRoomIndex && endVisible) {
                g2.setColor(new Color(0, 200, 0));
            } else if (visited != null && i < visited.length && visited[i]) {
                g2.setColor(new Color(220, 220, 220));
            } else {
                g2.setColor(new Color(120, 120, 120));
            }
            g2.fillRect(x, y, roomSize, roomSize);

            if (i == playerRoomIndex) {
                g2.setColor(Color.YELLOW);
                g2.drawRect(x - 1, y - 1, roomSize + 1, roomSize + 1);
            }
        }
    }

    private void drawLine2px(Graphics2D g2, int x1, int y1, int x2, int y2){
        if (x1 == x2){
            int yStart = Math.min(y1, y2);
            int yEnd = Math.max(y1, y2);
            g2.fillRect(x1 - 1, yStart, 2, yEnd - yStart + 1);
        } else if (y1 == y2){
            int xStart = Math.min(x1, x2);
            int xEnd = Math.max(x1, x2);
            g2.fillRect(xStart, y1 - 1, xEnd - xStart + 1, 2);
        } else {
            g2.drawLine(x1, y1, x2, y2);
        }
    }
}
