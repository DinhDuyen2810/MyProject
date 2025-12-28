package entity;

import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.geom.AffineTransform;
import java.awt.image.BufferedImage;
import java.io.IOException;

import javax.imageio.ImageIO;

import main.GamePanel;
import main.KeyHandler;

public class Player extends Entity{
    GamePanel gp;
    KeyHandler keyH;
    public int hasDiamond = 0;

    public final double screenX;
    public final double screenY;
    
    public Player(GamePanel gp, KeyHandler keyH){
        this.gp = gp;
        this.keyH = keyH;
        
        setDefaultValues();
        getPlayerImage();

        screenX = gp.screenWidth / 2 - (up1.getWidth() / 4);
        screenY = gp.screenHeight / 2 - (up1.getHeight() / 4);
        solidPoint = new Point((int)(up1.getWidth() * 0.6 / 2), (int)(up1.getHeight() * 0.6));  
        // để cho point nằm ngay dưới chân player(tỷ lệ theo ảnh)
        // 0.6 is scale
        solidPointDefaultX = solidPoint.x;
        solidPointDefaultY = solidPoint.y;
    }

    public void setDefaultValues(){
        worldX = gp.tileSize * 40;
        worldY = gp.tileSize * 10;
        speed = 2;
        direction = "down";
    }

    public void getPlayerImage(){

        try{
            up1 = ImageIO.read(getClass().getResourceAsStream("/res/player/player_up1.png"));
            up2 = ImageIO.read(getClass().getResourceAsStream("/res/player/player_up2.png"));
            up3 = ImageIO.read(getClass().getResourceAsStream("/res/player/player_up3.png"));
            down1 = ImageIO.read(getClass().getResourceAsStream("/res/player/player_down1.png"));
            down2 = ImageIO.read(getClass().getResourceAsStream("/res/player/player_down2.png"));
            down3 = ImageIO.read(getClass().getResourceAsStream("/res/player/player_down3.png"));
            left1 = ImageIO.read(getClass().getResourceAsStream("/res/player/player_left1.png"));
            left2 = ImageIO.read(getClass().getResourceAsStream("/res/player/player_left2.png"));
            left3 = ImageIO.read(getClass().getResourceAsStream("/res/player/player_left3.png"));
            right1 = ImageIO.read(getClass().getResourceAsStream("/res/player/player_right1.png"));
            right2 = ImageIO.read(getClass().getResourceAsStream("/res/player/player_right2.png"));
            right3 = ImageIO.read(getClass().getResourceAsStream("/res/player/player_right3.png"));
        } catch (IOException e){
            e.printStackTrace();
        }
    }
    
    public void update(){
        if(keyH.isUpPressed || keyH.isDownPressed || keyH.isLeftPressed || keyH.isRightPressed){
            double dx = 0, dy = 0;
            if(keyH.isUpPressed == true){
                direction = "up";
                dy = -speed;
            }
            if(keyH.isDownPressed == true){
                direction = "down";
                dy = speed;
            }
            if(keyH.isLeftPressed == true){
                direction = "left"; 
                dx = -speed;
            }
            if(keyH.isRightPressed == true){
                direction = "right";       
                dx = speed;
            }

            collisionOn = false;
            // Kiểm tra va chạm với các đối tượng
            gp.cChecker.checkTile(this);
            int objIndex = gp.cChecker.checkObject(this, true);
            pickUpObj(objIndex);


            if(collisionOn == false){
    
                // Nếu đang di chuyển chéo, chia giảm vận tốc
                if (dx != 0 && dy != 0) {
                    dx /= 1.4142;
                    dy /= 1.4142;
                }

                // Cập nhật vị trí
                worldX += dx;
                worldY += dy;
            }

            spriteCounter++;
            if(spriteCounter > 6){
                spriteNum = spriteNum % 3 + 1;
                spriteCounter = 0;
            }
        } else {
            spriteNum = 2;
        }
        
    }
    int voiceSecond = 0;
    public void pickUpObj(int index){
        if(index != 999){
            String objName = gp.obj[index].name;
            voiceSecond = voiceSecond % 10 + 1;

            switch(objName){
                case "diamond":
                    hasDiamond++;
                    gp.obj[index] = null;
                    gp.ui.showMessage("You got a diamond!");
                    break;
                case "door":
                    if(voiceSecond == 1){
                        gp.playSound(1);
                    }
                    if(hasDiamond >= 3){
                        gp.ui.showMessage("Comming soon bro!");
                    } else {
                        gp.ui.showMessage("You need 3 diamonds!");
                    }
                    break;
                default:
                    System.out.println("not diamond!");
            }
        }
    }
    
    public void draw(Graphics2D g2){

        BufferedImage image = null;
        switch(direction){
            case "up":
            if(spriteNum == 1){
                    image = up1;
                } else if(spriteNum == 2){
                    image = up3;
                } else if(spriteNum == 3){
                    image = up2;
                }
                break;
            case "down":
                if(spriteNum == 1){
                    image = down1;
                } else if(spriteNum == 2){
                    image = down3;
                } else if(spriteNum == 3){
                    image = down2;
                }
                break;
            case "left":
                if(spriteNum == 1){
                    image = left1;
                } else if(spriteNum == 2){
                    image = left3;
                } else if(spriteNum == 3){
                    image = left2;
                }
                break;
            case "right":
                if(spriteNum == 1){
                    image = right1;
                } else if(spriteNum == 2){
                    image = right3;
                } else if(spriteNum == 3){
                    image = right2;
                }
                break;
        }
        AffineTransform at = new AffineTransform();
        at.translate(screenX, screenY);
        at.scale(0.6, 0.6);         // origin is 96 x 96
        g2.drawImage(image, at, null);
        

    }
}
