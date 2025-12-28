package main;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;

import object.OBJ_Diamond;

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
        OBJ_Diamond diamond = new OBJ_Diamond();
        diamondImage = diamond.image;
    }

    public void showMessage(String message){
        this.message = message;
        messageOn = true;
    }

    public void draw(Graphics2D g2){
        g2.setFont(arial_20);
        g2.setColor(Color.WHITE);
        g2.drawString("FPS: " + gp.FPS, 10, 20);
        g2.drawString("x: " + (gp.player.worldX + gp.player.solidPoint.x) + "  y: "
                            + (gp.player.worldY + gp.player.solidPoint.y), 10, 40);
        g2.drawImage(diamondImage, 10, 50, gp.tileSize, gp.tileSize, null);
        g2.drawString("x " + gp.player.hasDiamond, 40, 73);

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
}
