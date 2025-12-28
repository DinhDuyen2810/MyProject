package object;

import java.io.IOException;

import javax.imageio.ImageIO;

public class OBJ_Bed extends SuperObject{
    public OBJ_Bed() {
        name = "bed";
        normalX = 2;
        normalY = 2;
        try{
            image = ImageIO.read(getClass().getResourceAsStream("/res/objects/bed_block.png"));
        } catch(IOException e){
            e.printStackTrace();
        }
        solidArea.height *= normalX;
        solidArea.width *= normalY;
    }
}
