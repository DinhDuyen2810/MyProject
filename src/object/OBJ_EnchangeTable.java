package object;

import java.awt.image.BufferedImage;
import java.awt.image.RasterFormatException;
import java.io.IOException;
import javax.imageio.ImageIO;
import tile.VideoTile;

public class OBJ_EnchangeTable extends SuperObject {

    private VideoTile anim = null;

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
            // Prefer a single spritesheet: enchange_table.png
            java.io.InputStream is = getClass().getResourceAsStream("/res/objects/enchange_table.png");
            if (is == null) {
                System.out.println("OBJ_EnchangeTable: resource not found: /res/objects/enchange_table.png");
            } else {
                BufferedImage sprite = ImageIO.read(is);
                if (sprite == null) {
                    System.out.println("OBJ_EnchangeTable: ImageIO.read returned null for enchange_table.png");
                } else {
                    int spriteW = sprite.getWidth();
                    int spriteH = sprite.getHeight();

                    // compute frame height per object aspect ratio: frameH = spriteW * normalY / normalX
                    if (spriteW > 0 && normalX > 0) {
                        double perFrameHdouble = ((double) spriteW) * ((double) normalY / (double) normalX);
                        int perFrameH = (int) Math.round(perFrameHdouble);
                        int frameCount = perFrameH > 0 ? (spriteH / perFrameH) : 0;

                        System.out.println("OBJ_EnchangeTable: sprite found (w=" + spriteW + ", h=" + spriteH + ") normalX=" + normalX + " normalY=" + normalY + " => frameH=" + perFrameH + " frames=" + frameCount);

                        if (frameCount >= 1) {
                            java.util.List<BufferedImage> framesRaw = new java.util.ArrayList<>();
                            for (int i = 0; i < frameCount; i++) {
                                int y = i * perFrameH;
                                int h = Math.min(perFrameH, spriteH - y);
                                try {
                                    BufferedImage f = sprite.getSubimage(0, y, spriteW, h);
                                    framesRaw.add(f);
                                } catch (RasterFormatException rfe) {
                                    System.err.println("OBJ_EnchangeTable: subimage error i=" + i + " -> " + rfe.getMessage());
                                }
                            }

                            // keep original frame pixel size; drawing will scale in SuperObject.drawImage
                            anim = VideoTile.fromFrames(framesRaw, spriteW, perFrameH);
                            if (anim != null && anim.isLoaded()) {
                                // speed up animation: halve frame delay to double speed
                                anim.multiplyFrameDelay(0.5);
                                image = anim.getCurrentFrameImage();
                            }
                            return;
                        }
                    }
                }
            }
            // No spritesheet found; leave image null so object won't render.
        } catch (IOException | IllegalArgumentException e) {
            image = null;
        }
    }

    @Override
    public void update() {
        if (anim != null && anim.isLoaded()) {
            anim.update();
            image = anim.getCurrentFrameImage();
        }
    }
}
