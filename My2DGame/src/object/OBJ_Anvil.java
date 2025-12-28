package object;

import java.io.IOException;
import javax.imageio.ImageIO;

public class OBJ_Anvil extends SuperObject{
    public OBJ_Anvil() {
        name = "anvil";
        normalX = 1;
        normalY = 2;
        try{
            image = ImageIO.read(getClass().getResourceAsStream("/res/objects/anvil.png"));
        } catch(IOException e){
            e.printStackTrace();
        }
        solidArea.height *= normalX;
        solidArea.width *= normalY;
    }
}
