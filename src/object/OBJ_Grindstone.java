package object;

import java.io.IOException;
import javax.imageio.ImageIO;

public class OBJ_Grindstone extends SuperObject{
    public OBJ_Grindstone() {
        name = "grindstone";
        normalX = 1;
        normalY = 1;
        try{
            image = ImageIO.read(getClass().getResourceAsStream("/res/objects/grind_stone.png"));
        } catch(IOException e){
            e.printStackTrace();
        }
        solidArea.width *= normalX;
        solidArea.height *= normalY;
    
    }

}
