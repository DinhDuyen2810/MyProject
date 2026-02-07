package object;

import java.io.IOException;
import javax.imageio.ImageIO;

public class OBJ_Smoker extends SuperObject{
    public OBJ_Smoker() {
        name = "smoker";
        normalX = 1;
        normalY = 2;
        try{
            image = ImageIO.read(getClass().getResourceAsStream("/res/objects/smoker.png"));
        } catch(IOException e){
            e.printStackTrace();
        }
        solidArea.width *= normalX;
        solidArea.height *= normalY;
        collision = true;
    }
}
