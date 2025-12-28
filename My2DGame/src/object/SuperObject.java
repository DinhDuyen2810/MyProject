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

    public void update() {
        
    }


    public void draw(Graphics2D g2, GamePanel gp){
        double screenX = worldX - gp.player.worldX + gp.player.screenX;
        double screenY = worldY - gp.player.worldY + gp.player.screenY;

        if(worldX + gp.tileSize * normalX > gp.player.worldX - gp.player.screenX - gp.tileSize &&
                worldX - gp.tileSize * normalX < gp.player.worldX + gp.player.screenX + gp.tileSize &&
                    worldY + gp.tileSize * normalY > gp.player.worldY - gp.player.screenY - gp.tileSize &&
                        worldY - gp.tileSize * normalY < gp.player.worldY + gp.player.screenY + gp.tileSize){
                            
            g2.drawImage(image, 
                        (int)Math.round(screenX) - (normalX / 2) * gp.tileSize,
                        (int)Math.round(screenY) - (normalY - 1) * gp.tileSize, 
                        gp.tileSize * normalX,
                        gp.tileSize * normalY, null);
        }
    }

}
