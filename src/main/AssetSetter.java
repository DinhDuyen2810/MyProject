package main;

import object.OBJ_Anvil;
import object.OBJ_Bed;
import object.OBJ_BookShelf;
import object.OBJ_BrewingStand;
import object.OBJ_Cauldron;
import object.OBJ_Chest;
import object.OBJ_CraftBlock;
import object.OBJ_Door;
import object.OBJ_EnchangeTable;
import object.OBJ_Furnace;
import object.OBJ_Grindstone;
import object.OBJ_Luckyblock;
import object.OBJ_Smeltery;
import object.OBJ_Smoker;
import object.OBJ_Composter;

public class AssetSetter {
    GamePanel gp;

    public AssetSetter(GamePanel gp){
        this.gp = gp;
    }

    public void setObject(){


        gp.obj[1] = new OBJ_Door();
        gp.obj[1].worldX = 42 * gp.tileSize;
        gp.obj[1].worldY = 1 * gp.tileSize;
        
        gp.obj[2] = new OBJ_Chest();
        gp.obj[2].worldX = 40 * gp.tileSize;
        gp.obj[2].worldY = 2 * gp.tileSize;
        
        gp.obj[3] = new OBJ_Bed();
        gp.obj[3].worldX = 36 * gp.tileSize;
        gp.obj[3].worldY = 14 * gp.tileSize;
        
        gp.obj[4] = new OBJ_CraftBlock();
        gp.obj[4].worldX = 64 * gp.tileSize;
        gp.obj[4].worldY = 14 * gp.tileSize;
        
        gp.obj[5] = new OBJ_Furnace();
        gp.obj[5].worldX = 55 * gp.tileSize;
        gp.obj[5].worldY = 4 * gp.tileSize;
        
        gp.obj[6] = new OBJ_EnchangeTable();
        gp.obj[6].worldX = 66 * gp.tileSize;
        gp.obj[6].worldY = 5 * gp.tileSize;

        gp.obj[7] = new OBJ_BrewingStand();
        gp.obj[7].worldX = 56 * gp.tileSize;
        gp.obj[7].worldY = 14 * gp.tileSize;

        gp.obj[8] = new OBJ_Cauldron();
        gp.obj[8].worldX = 55 * gp.tileSize;
        gp.obj[8].worldY = 13 * gp.tileSize;

        gp.obj[9] = new OBJ_CraftBlock();
        gp.obj[9].worldX = 63 * gp.tileSize;
        gp.obj[9].worldY = 14 * gp.tileSize;

        gp.obj[10] = new OBJ_Furnace();
        gp.obj[10].worldX = 55 * gp.tileSize;
        gp.obj[10].worldY = 5 * gp.tileSize;

        gp.obj[11] = new OBJ_BookShelf();
        gp.obj[11].worldX = 65 * gp.tileSize;
        gp.obj[11].worldY = 3 * gp.tileSize;

        gp.obj[12] = new OBJ_BookShelf();
        gp.obj[12].worldX = 66 * gp.tileSize;
        gp.obj[12].worldY = 3 * gp.tileSize;

        gp.obj[13] = new OBJ_BookShelf();
        gp.obj[13].worldX = 67 * gp.tileSize;
        gp.obj[13].worldY = 3 * gp.tileSize;

        gp.obj[14] = new OBJ_BookShelf();
        gp.obj[14].worldX = 64 * gp.tileSize;
        gp.obj[14].worldY = 4 * gp.tileSize;

        gp.obj[15] = new OBJ_BookShelf();
        gp.obj[15].worldX = 64 * gp.tileSize;
        gp.obj[15].worldY = 5 * gp.tileSize;

        gp.obj[16] = new OBJ_BookShelf();
        gp.obj[16].worldX = 64 * gp.tileSize;
        gp.obj[16].worldY = 6 * gp.tileSize;

        gp.obj[17] = new OBJ_BookShelf();
        gp.obj[17].worldX = 68 * gp.tileSize;
        gp.obj[17].worldY = 4 * gp.tileSize;

        gp.obj[18] = new OBJ_BookShelf();
        gp.obj[18].worldX = 68 * gp.tileSize;
        gp.obj[18].worldY = 5 * gp.tileSize;

        gp.obj[19] = new OBJ_BookShelf();
        gp.obj[19].worldX = 68 * gp.tileSize;
        gp.obj[19].worldY = 6 * gp.tileSize;

        gp.obj[20] = new OBJ_Anvil();
        gp.obj[20].worldX = 68 * gp.tileSize;
        gp.obj[20].worldY = 9 * gp.tileSize;

        gp.obj[21] = new OBJ_Grindstone();
        gp.obj[21].worldX = 68 * gp.tileSize;
        gp.obj[21].worldY = 10 * gp.tileSize;

        gp.obj[22] = new OBJ_Luckyblock();
        gp.obj[22].worldX = 36 * gp.tileSize;
        gp.obj[22].worldY = 3 * gp.tileSize;

        gp.obj[23] = new OBJ_Smeltery();
        gp.obj[23].worldX = 56 * gp.tileSize;
        gp.obj[23].worldY = 3 * gp.tileSize;

        gp.obj[24] = new OBJ_Smeltery();
        gp.obj[24].worldX = 57 * gp.tileSize;
        gp.obj[24].worldY = 3 * gp.tileSize;

        gp.obj[25] = new OBJ_Smoker();
        gp.obj[25].worldX = 58 * gp.tileSize;
        gp.obj[25].worldY = 3 * gp.tileSize;

        gp.obj[26] = new OBJ_Smoker();
        gp.obj[26].worldX = 59 * gp.tileSize;
        gp.obj[26].worldY = 3 * gp.tileSize;

        gp.obj[27] = new OBJ_Chest();
        gp.obj[27].worldX = 66 * gp.tileSize;
        gp.obj[27].worldY = 14 * gp.tileSize;

        gp.obj[28] = new OBJ_Composter();
        gp.obj[28].worldX = 22 * gp.tileSize;
        gp.obj[28].worldY = 4 * gp.tileSize;

        gp.obj[29] = new OBJ_Composter();
        gp.obj[29].worldX = 22 * gp.tileSize;
        gp.obj[29].worldY = 5 * gp.tileSize;

        gp.obj[30] = new OBJ_Composter();
        gp.obj[30].worldX = 23 * gp.tileSize;
        gp.obj[30].worldY = 4 * gp.tileSize;

        gp.obj[31] = new OBJ_Composter();
        gp.obj[31].worldX = 23 * gp.tileSize;
        gp.obj[31].worldY = 5 * gp.tileSize;

    }
}
