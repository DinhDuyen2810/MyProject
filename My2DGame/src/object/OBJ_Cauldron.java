package object;

import java.io.IOException;

import javax.imageio.ImageIO;

public class OBJ_Cauldron extends SuperObject{
    public OBJ_Cauldron() {
        name = "cauldron";
        normalX = 1;
        normalY = 2;
        try{
            image = ImageIO.read(getClass().getResourceAsStream("/res/objects/cauldron.png"));
        } catch(IOException e){
            e.printStackTrace();
        }
        solidArea.height *= normalX;
        solidArea.width *= normalY;
    }
}
