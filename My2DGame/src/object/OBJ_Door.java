package object;

import java.io.IOException;

import javax.imageio.ImageIO;

public class OBJ_Door  extends SuperObject{
    
    public OBJ_Door() {
        name = "door";
        normalX = 2;
        normalY = 2;
        try{
            image = ImageIO.read(getClass().getResourceAsStream("/res/objects/door.png"));
        } catch(IOException e){
            e.printStackTrace();
        }
        solidArea.height *= normalX;
        solidArea.width *= normalY;
        collision = true;
    }
}
