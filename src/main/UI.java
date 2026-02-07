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
