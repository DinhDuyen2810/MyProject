package object;

import java.io.IOException;

import javax.imageio.ImageIO;

public class OBJ_Composter extends SuperObject {

    public OBJ_Composter() {
        name = "composter";
        normalX = 1;
        normalY = 2;
        collision = true;

        solidArea.height *= normalY;
        solidArea.width *= normalX;

        try {
            image = ImageIO.read(getClass().getResourceAsStream("/res/objects/composter.png"));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
