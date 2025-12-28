package object;

import java.io.IOException;

import javax.imageio.ImageIO;

public class OBJ_CraftBlock extends SuperObject{
    public OBJ_CraftBlock() {
        name = "craft_block";
        normalX = 1;
        normalY = 2;
        try{
            image = ImageIO.read(getClass().getResourceAsStream("/res/objects/craft_block.png"));
        } catch(IOException e){
            e.printStackTrace();
        }
        solidArea.height *= normalX;
        solidArea.width *= normalY;
        collision = true;
    }
}
