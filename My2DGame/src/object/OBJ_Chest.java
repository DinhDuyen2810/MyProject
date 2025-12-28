package object;

import java.io.IOException;
import javax.imageio.ImageIO;

public class OBJ_Chest extends SuperObject{
    public OBJ_Chest() {
        name = "chest";
        normalX = 2;
        normalY = 2;
        try{
            image = ImageIO.read(getClass().getResourceAsStream("/res/objects/long_chest_block.png"));
        } catch(IOException e){
            e.printStackTrace();
        }
        solidArea.height *= normalX;
        solidArea.width *= normalY;
        collision = true;
    }
}
