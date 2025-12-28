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

        if(worldX + gp.tileSize > gp.player.worldX - gp.player.screenX &&
                worldX - 3 * gp.tileSize < gp.player.worldX + gp.player.screenX &&
                    worldY + gp.tileSize > gp.player.worldY - gp.player.screenY &&
                        worldY - 3 * gp.tileSize < gp.player.worldY + gp.player.screenY){
                            
            g2.drawImage(image, 
                        (int)screenX - (normalX / 2) * gp.tileSize,
                        (int)screenY - (normalY - 1) * gp.tileSize, 
                        gp.tileSize * normalX,
                        gp.tileSize * normalY, null);
        }
    }

}
