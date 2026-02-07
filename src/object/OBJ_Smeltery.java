package object;

import java.io.IOException;
import javax.imageio.ImageIO;

public class OBJ_Smeltery extends SuperObject{

    public OBJ_Smeltery() {
        name = "smeltery";
        normalX = 1;
        normalY = 2;
        try{
            image = ImageIO.read(getClass().getResourceAsStream("/res/objects/smeltery.png"));
        } catch(IOException e){
            e.printStackTrace();
        }
        solidArea.width *= normalX;
        solidArea.height *= normalY;
        collision = true;
    }

}
