package object;

import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.image.BufferedImage;

import main.GamePanel;

public class SuperObject {
    public BufferedImage image;
    public String name;
    public int worldX, worldY;
    public int normalX = 1, normalY = 1;
    public boolean collision = false;

    public Rectangle solidArea = new Rectangle(0, 0, 30, 30);
    public int solidDefaultAreaX = 0;
    public int solidDefaultAreaY = 0;

    // return collision rectangle in world coordinates
    // collision box is always at the bottom of the object
    public java.awt.Rectangle getCollisionRect(GamePanel gp){
        int w = normalX * gp.tileSize;
        int h = normalY * gp.tileSize;
        int collW = gp.tileSize; // default 1 tile wide
        int collH = gp.tileSize; // default 1 tile high

        int offsetX = 0;
        int offsetY = (normalY - 1) * gp.tileSize; // default bottom

        if(normalX == 1 && normalY == 2){
            collW = gp.tileSize;
            collH = gp.tileSize;
            offsetX = 0;
            offsetY = gp.tileSize; // bottom of 2-high
        } else if(normalX == 2 && normalY == 2){
            collW = 2 * gp.tileSize;
            collH = gp.tileSize;
            offsetX = 0;
            offsetY = gp.tileSize;
        } else if(normalX == 3 && normalY == 3){
            collW = gp.tileSize;
            collH = gp.tileSize;
            offsetX = gp.tileSize; // center
            offsetY = 2 * gp.tileSize;
        }

        int x = worldX + offsetX - (normalX / 2) * gp.tileSize;
        int y = worldY + offsetY - (normalY - 1) * gp.tileSize;
        return new java.awt.Rectangle(x, y, collW, collH);
    }

    public void update() {
        
    }


    // draw when object should appear before player
    public void drawFirst(Graphics2D g2, GamePanel gp){
        java.awt.Rectangle crect = getCollisionRect(gp);
        java.awt.Rectangle prect = gp.player.getCollisionRect(gp);
        // object is above player
        if(crect.y + crect.height <= prect.y){
            drawImage(g2, gp);
        }
    }

    // draw when object should appear after player
    public void drawLast(Graphics2D g2, GamePanel gp){
        java.awt.Rectangle crect = getCollisionRect(gp);
        java.awt.Rectangle prect = gp.player.getCollisionRect(gp);
        // draw if object's bottom is below player's top (covers overlap case)
        if (crect.y + crect.height > prect.y) {
            drawImage(g2, gp);
        }
    }

    // helper to draw image without depth logic
    public void drawImage(Graphics2D g2, GamePanel gp){
        double screenX = worldX - gp.player.worldX + gp.player.screenX;
        double screenY = worldY - gp.player.worldY + gp.player.screenY;
        g2.drawImage(image,
                (int)Math.round(screenX) - (normalX / 2) * gp.tileSize,
                (int)Math.round(screenY) - (normalY - 1) * gp.tileSize,
                gp.tileSize * normalX,
                gp.tileSize * normalY, null);
    }

}
