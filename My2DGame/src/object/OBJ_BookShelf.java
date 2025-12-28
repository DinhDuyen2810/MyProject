package object;

import java.io.IOException;

import javax.imageio.ImageIO;

public class OBJ_BookShelf extends SuperObject{
    public OBJ_BookShelf() {
        name = "book_shelf_block";
        normalX = 1;
        normalY = 3;
        try{
            image = ImageIO.read(getClass().getResourceAsStream("/res/objects/book_shelf_block_3.png"));
        } catch(IOException e){
            e.printStackTrace();
        }
        solidArea.height *= normalX;
        solidArea.width *= normalY;
    }
}
