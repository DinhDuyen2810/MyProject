package object;

import java.io.IOException;

import javax.imageio.ImageIO;

public class OBJ_BrewingStand extends SuperObject{
    public OBJ_BrewingStand() {
        name = "brewing_stand";
        normalX = 1;
        normalY = 1;
        try{
            image = ImageIO.read(getClass().getResourceAsStream("/res/objects/brewing_stand.png"));
        } catch(IOException e){
            e.printStackTrace();
        }
        solidArea.height *= normalX;
        solidArea.width *= normalY;
        collision = true;
    }
}
