package object;

import java.io.IOException;
import javax.imageio.ImageIO;

public class OBJ_Luckyblock extends SuperObject{
    public OBJ_Luckyblock() {
        name = "luckyblock";
        normalX = 1;
        normalY = 2;
        try{
            image = ImageIO.read(getClass().getResourceAsStream("/res/objects/lucky_block.png"));
        } catch(IOException e){
            e.printStackTrace();
        }
        solidArea.width *= normalX;
        solidArea.height *= normalY;
    }
}
