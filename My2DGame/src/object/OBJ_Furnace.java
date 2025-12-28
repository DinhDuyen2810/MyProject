package object;

import java.io.IOException;

import javax.imageio.ImageIO;

public class OBJ_Furnace extends SuperObject{
    public OBJ_Furnace() {
        name = "furnace";
        normalX = 1;
        normalY = 2;
        try{
            image = ImageIO.read(getClass().getResourceAsStream("/res/objects/furnace_block.png"));
        } catch(IOException e){
            e.printStackTrace();
        }
        solidArea.height *= normalX;
        solidArea.width *= normalY;
        collision = true;
    }
}
