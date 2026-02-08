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
        if (dungeon == null || dungeon.mapTiles == null) return;

        int cols = dungeon.mapTiles.length;
        int rows = dungeon.mapTiles[0].length;

        int margin = 10;
        int maxSize = 160;

        double scaleX = (double)maxSize / cols;
        double scaleY = (double)maxSize / rows;
        double scale = Math.min(scaleX, scaleY);

        int mapW = (int)Math.round(cols * scale);
        int mapH = (int)Math.round(rows * scale);

        int originX = gp.screenWidth - mapW - margin;
        int originY = margin;

        // background panel
        g2.setColor(new Color(0, 0, 0, 160));
        g2.fillRect(originX - 4, originY - 4, mapW + 8, mapH + 8);

        // tiles
        for (int x = 0; x < cols; x++){
            for (int y = 0; y < rows; y++){
                int tile = dungeon.mapTiles[x][y];
                if (tile == 1){
                    g2.setColor(new Color(146, 112, 72)); // dirt
                } else {
                    g2.setColor(new Color(30, 30, 30)); // void
                }
                int px = originX + (int)Math.round(x * scale);
                int py = originY + (int)Math.round(y * scale);
                int pw = Math.max(1, (int)Math.ceil(scale));
                int ph = Math.max(1, (int)Math.ceil(scale));
                g2.fillRect(px, py, pw, ph);
            }
        }

        // door position (end room center)
        int doorX = originX + (int)Math.round(dungeon.endX * scale);
        int doorY = originY + (int)Math.round(dungeon.endY * scale);
        g2.setColor(Color.RED);
        g2.fillOval(doorX - 2, doorY - 2, 5, 5);

        // player position
        int playerTileX = (int)Math.round(gp.player.worldX / gp.tileSize);
        int playerTileY = (int)Math.round(gp.player.worldY / gp.tileSize);
        int playerX = originX + (int)Math.round(playerTileX * scale);
        int playerY = originY + (int)Math.round(playerTileY * scale);
        g2.setColor(Color.YELLOW);
        g2.fillOval(playerX - 2, playerY - 2, 5, 5);
    }
}
