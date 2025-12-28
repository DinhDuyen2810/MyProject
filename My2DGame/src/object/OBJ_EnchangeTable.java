package object;

import java.io.IOException;
import javax.imageio.ImageIO;

public class OBJ_EnchangeTable extends SuperObject {

    private static final int MAX_FRAME = 18;

    private int frameIndex = 1;
    private int frameCounter = 0;
    private int frameSpeed = 2;

    public OBJ_EnchangeTable() {

        name = "enchange_table";
        normalX = 1;
        normalY = 2;
        collision = true;

        solidArea.height *= normalY;
        solidArea.width  *= normalX;

        loadImage();
    }

    private void loadImage() {
        try {
            image = ImageIO.read(
                getClass().getResourceAsStream(
                    "/res/objects/enchange_table_" + frameIndex + ".png"
                )
            );
        } catch (IOException | IllegalArgumentException e) {
            image = null;
        }
    }

    @Override
    public void update() {

        frameCounter++;

        if (frameCounter >= frameSpeed) {
            frameIndex++;
            if (frameIndex > MAX_FRAME) {
                frameIndex = 1;
            }
            loadImage();
            frameCounter = 0;
        }
    }
}
