package object;

import java.io.IOException;
import javax.imageio.ImageIO;

public class OBJ_Diamond  extends SuperObject{
    
    public OBJ_Diamond(){

        name = "diamond";
        try{
            image = ImageIO.read(getClass().getResourceAsStream("/res/objects/diamond.png"));
        } catch(IOException e){
            e.printStackTrace();
        }
    }
}
