package main;

import entity.Entity;
import tile.Tile;

public class CollisionChecker {
    GamePanel gp;

    public CollisionChecker(GamePanel gp){
        this.gp = gp;
    }

    public void checkTile(Entity entity){
        // Use rectangle-based collision for tiles and float-tiles to avoid directional asymmetry.
        java.awt.Rectangle eRect;
        if (entity instanceof entity.Player) {
            eRect = ((entity.Player)entity).getCollisionRect(gp);
        } else {
            eRect = new java.awt.Rectangle((int)entity.worldX, (int)entity.worldY, gp.tileSize, gp.tileSize);
        }

        // compute movement delta based on direction and speed
        int dx = 0, dy = 0;
        switch(entity.direction){
            case "up": dy = (int)Math.floor(-entity.speed); break;
            case "down": dy = (int)Math.ceil(entity.speed); break;
            case "left": dx = (int)Math.floor(-entity.speed); break;
            case "right": dx = (int)Math.ceil(entity.speed); break;
        }

        java.awt.Rectangle moved = new java.awt.Rectangle(eRect);
        moved.translate(dx, dy);

        // compute tile range to inspect
        int leftCol = Math.max(0, (int)Math.floor((moved.x) / (double)gp.tileSize) - 1);
        int rightCol = Math.min(gp.tileM.mapCols - 1, (int)Math.floor((moved.x + moved.width) / (double)gp.tileSize) + 1);
        int topRow = Math.max(0, (int)Math.floor((moved.y) / (double)gp.tileSize) - 1);
        int bottomRow = Math.min(gp.tileM.mapRows - 1, (int)Math.floor((moved.y + moved.height) / (double)gp.tileSize) + 1);

        for (int col = leftCol; col <= rightCol; col++){
            for (int row = topRow; row <= bottomRow; row++){
                // check base tile collision map
                if (gp.tileM.mapCollisionTile != null){
                    try{
                        if (gp.tileM.mapCollisionTile[col][row] == 1){
                            java.awt.Rectangle tRect = new java.awt.Rectangle(col * gp.tileSize, row * gp.tileSize, gp.tileSize, gp.tileSize);
                            if (moved.intersects(tRect)){
                                entity.collisionOn = true;
                                return;
                            }
                        }
                    } catch(Exception ex){ /* ignore OOB */ }
                }

                // check float tile collisions
                if (gp.fTileM.mapfloatTileNum != null){
                    try{
                        int tileNum = gp.fTileM.mapfloatTileNum[col][row];
                        if (tileNum > 0 && tileNum < gp.fTileM.floatTile.length){
                            Tile t = gp.fTileM.floatTile[tileNum];
                            if (t != null && t.collision){
                                // compute float tile collision rect in world coords
                                int collW = gp.tileSize;
                                int collH = gp.tileSize;
                                int offsetX = 0;
                                int offsetY = (t.normalY - 1) * gp.tileSize;
                                if (t.normalX == 1 && t.normalY == 2){ collW = gp.tileSize; collH = gp.tileSize; offsetX = 0; offsetY = gp.tileSize; }
                                else if (t.normalX == 2 && t.normalY == 2){ collW = 2 * gp.tileSize; collH = gp.tileSize; offsetX = 0; offsetY = gp.tileSize; }
                                else if (t.normalX == 3 && t.normalY == 3){ collW = gp.tileSize; collH = gp.tileSize; offsetX = gp.tileSize; offsetY = 2 * gp.tileSize; }

                                int wx = col * gp.tileSize + offsetX - (t.normalX / 2) * gp.tileSize;
                                int wy = row * gp.tileSize + offsetY - (t.normalY - 1) * gp.tileSize;
                                java.awt.Rectangle fRect = new java.awt.Rectangle(wx, wy, collW, collH);
                                if (moved.intersects(fRect)){
                                    entity.collisionOn = true;
                                    return;
                                }
                            }
                        }
                    } catch(Exception ex){ /* ignore OOB */ }
                }
            }
        }
        
    }
        
    
    public int checkObject(Entity entity, boolean player){
        int index = 999;
        for(int i = 0; i < gp.obj.length; i++){
            if(gp.obj[i] != null){
                // build entity collision rect (same as checkTile)
                java.awt.Rectangle eRect;
                if (entity instanceof entity.Player) {
                    eRect = ((entity.Player)entity).getCollisionRect(gp);
                } else {
                    eRect = new java.awt.Rectangle((int)entity.worldX, (int)entity.worldY, gp.tileSize, gp.tileSize);
                }

                // compute movement delta based on direction and speed (same rules as checkTile)
                int dx = 0, dy = 0;
                switch(entity.direction){
                    case "up": dy = (int)Math.floor(-entity.speed); break;
                    case "down": dy = (int)Math.ceil(entity.speed); break;
                    case "left": dx = (int)Math.floor(-entity.speed); break;
                    case "right": dx = (int)Math.ceil(entity.speed); break;
                }

                java.awt.Rectangle moved = new java.awt.Rectangle(eRect);
                moved.translate(dx, dy);

                // get object's collision rectangle (world coords)
                java.awt.Rectangle objRect = gp.obj[i].getCollisionRect(gp);

                // rectangle-vs-rectangle intersection (x1,x2,y1,y2 logic)
                if (moved.intersects(objRect)){
                    if(gp.obj[i].collision == true){
                        entity.collisionOn = true;
                    }
                    if(player == true){
                        index = i;
                    }
                }
            }
        }


        return index;
    }
}
