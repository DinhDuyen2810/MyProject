package main;

import entity.Entity;

public class CollisionChecker {
    GamePanel gp;

    public CollisionChecker(GamePanel gp){
        this.gp = gp;
    }

    public void checkTile(Entity entity){
        double entityX = (entity.worldX + entity.solidPoint.x) / gp.tileSize;
        double entityY = (entity.worldY + entity.solidPoint.y) / gp.tileSize;


        int tile1Check, tile2Check;
        int floatTile1Check, floatTile2Check;

        switch(entity.direction){
            case "up":
                tile1Check = gp.tileM.mapCollisionTile[(int)entityX]
                                                    [(int)(entityY - 4 * entity.speed / gp.tileSize)];
                tile2Check = gp.tileM.mapCollisionTile[(int)entityX]
                                                    [(int)(entityY - 4 * entity.speed / gp.tileSize)];
                floatTile1Check = gp.fTileM.mapCollisionFTile[(int)entityX]
                                                    [(int)(entityY - 4 * entity.speed / gp.tileSize)];
                floatTile2Check = gp.fTileM.mapCollisionFTile[(int)entityX]
                                                    [(int)(entityY - 4 * entity.speed / gp.tileSize)];
                if(entityX - (int)(entityX) > 0.6){
                    tile2Check = gp.tileM.mapCollisionTile[(int)entityX + 1]
                                                    [(int)(entityY - 4 * entity.speed / gp.tileSize)];
                    floatTile2Check = gp.fTileM.mapCollisionFTile[(int)entityX + 1]
                                                    [(int)(entityY - 4 * entity.speed / gp.tileSize)];
                } else if(entityX - (int)(entityX) < 0.4) {
                    tile2Check = gp.tileM.mapCollisionTile[(int)entityX - 1]
                                                    [(int)(entityY - 4 * entity.speed / gp.tileSize)];
                    floatTile2Check = gp.fTileM.mapCollisionFTile[(int)entityX - 1]
                                                    [(int)(entityY - 4 * entity.speed / gp.tileSize)];
                }
                                        
                if(tile1Check == 1 || tile2Check == 1 || floatTile1Check == 1 || floatTile2Check == 1){
                    entity.collisionOn = true;
                }
                        
                
                break;
            case "down":
                tile1Check = gp.tileM.mapCollisionTile[(int)entityX]
                                                    [(int)(entityY + 4 * entity.speed / gp.tileSize)];
                tile2Check = gp.tileM.mapCollisionTile[(int)entityX]
                                                    [(int)(entityY + 4 * entity.speed / gp.tileSize)];
                floatTile1Check = gp.fTileM.mapCollisionFTile[(int)entityX]
                                                    [(int)(entityY + 4 * entity.speed / gp.tileSize)];
                floatTile2Check = gp.fTileM.mapCollisionFTile[(int)entityX]
                                                    [(int)(entityY + 4 * entity.speed / gp.tileSize)];
                if(entityX - (int)(entityX) > 0.6){
                    tile2Check = gp.tileM.mapCollisionTile[(int)entityX + 1]
                                                    [(int)(entityY + 4 * entity.speed / gp.tileSize)];
                    floatTile2Check = gp.fTileM.mapCollisionFTile[(int)entityX + 1]
                                                    [(int)(entityY + 4 * entity.speed / gp.tileSize)];
                } else if(entityX - (int)(entityX) < 0.4) {
                    tile2Check = gp.tileM.mapCollisionTile[(int)entityX - 1]
                                                    [(int)(entityY + 4 * entity.speed / gp.tileSize)];
                    floatTile2Check = gp.fTileM.mapCollisionFTile[(int)entityX - 1]
                                                    [(int)(entityY + 4 * entity.speed / gp.tileSize)];
                }
                if(tile1Check == 1 || tile2Check == 1 || floatTile1Check == 1 || floatTile2Check == 1){
                    entity.collisionOn = true;
                }
                
                break;
            case "left":
                tile1Check = gp.tileM.mapCollisionTile[(int)(entityX - 8 * entity.speed / gp.tileSize)]
                                                    [(int)entityY];
                tile2Check = gp.tileM.mapCollisionTile[(int)(entityX - 8 * entity.speed / gp.tileSize)]
                                                    [(int)entityY];
                floatTile1Check = gp.fTileM.mapCollisionFTile[(int)(entityX - 8 * entity.speed / gp.tileSize)]
                                                    [(int)entityY];
                floatTile2Check = gp.fTileM.mapCollisionFTile[(int)(entityX - 8 * entity.speed / gp.tileSize)]
                                                    [(int)entityY];
                if(entityY - (int)(entityY) > 0.9){
                    tile2Check = gp.tileM.mapCollisionTile[(int)(entityX - entity.speed / gp.tileSize)]
                                                    [(int)entityY + 1];
                    floatTile2Check = gp.fTileM.mapCollisionFTile[(int)(entityX - entity.speed / gp.tileSize)]
                                                    [(int)entityY + 1];
                } else if(entityY - (int)(entityY) < 0.1) {
                    tile2Check = gp.tileM.mapCollisionTile[(int)(entityX - entity.speed / gp.tileSize)]
                                                    [(int)entityY - 1];
                    floatTile2Check = gp.fTileM.mapCollisionFTile[(int)(entityX - entity.speed / gp.tileSize)]
                                                    [(int)entityY - 1];
                }
                if(tile1Check == 1 || tile2Check == 1 || floatTile1Check == 1 || floatTile2Check == 1){
                    entity.collisionOn = true;
                }
            
                
            break;
            case "right":
                tile1Check = gp.tileM.mapCollisionTile[(int)(entityX + 8 * entity.speed / gp.tileSize)]
                                                    [(int)entityY];
                tile2Check = gp.tileM.mapCollisionTile[(int)(entityX + 8 * entity.speed / gp.tileSize)]
                                                    [(int)entityY];
                floatTile1Check = gp.fTileM.mapCollisionFTile[(int)(entityX + 8 * entity.speed / gp.tileSize)]
                                                    [(int)entityY];
                floatTile2Check = gp.fTileM.mapCollisionFTile[(int)(entityX + 8 * entity.speed / gp.tileSize)]
                                                    [(int)entityY];
                if(entityY - (int)(entityY) > 0.9){
                    tile2Check = gp.tileM.mapCollisionTile[(int)(entityX - entity.speed / gp.tileSize)]
                                                    [(int)entityY + 1];
                    floatTile2Check = gp.fTileM.mapCollisionFTile[(int)(entityX - entity.speed / gp.tileSize)]
                                                    [(int)entityY + 1];
                } else if(entityY - (int)(entityY) < 0.1) {
                    tile2Check = gp.tileM.mapCollisionTile[(int)(entityX - entity.speed / gp.tileSize)]
                                                    [(int)entityY - 1];
                    floatTile2Check = gp.fTileM.mapCollisionFTile[(int)(entityX - entity.speed / gp.tileSize)]
                                                    [(int)entityY - 1];
                }
                if(tile1Check == 1 || tile2Check == 1 || floatTile1Check == 1 || floatTile2Check == 1){
                    entity.collisionOn = true;
                }
                
            break;
        }
        
    }
    
    public int checkObject(Entity entity, boolean player){
        int index = 999;
        for(int i = 0; i < gp.obj.length; i++){
            if(gp.obj[i] != null){
                entity.solidPoint.x = (int)(entity.worldX + entity.solidPoint.x);
                entity.solidPoint.y = (int)(entity.worldY + entity.solidPoint.y);

                gp.obj[i].solidArea.x = gp.obj[i].worldX + gp.obj[i].solidArea.x - (gp.obj[i].normalX / 2) * gp.tileSize;
                gp.obj[i].solidArea.y = gp.obj[i].worldY + gp.obj[i].solidArea.y - (gp.obj[i].normalY - 1) * gp.tileSize;

                switch(entity.direction){
                    case "up":
                        entity.solidPoint.y -= entity.speed;
                        if(gp.obj[i].solidArea.contains(entity.solidPoint)){
                            if(gp.obj[i].collision == true){
                                entity.collisionOn = true;
                            }
                            if(player == true){
                                index = i;
                            }
                        }
                        break;
                    case "down":
                        entity.solidPoint.y += entity.speed;
                        if(gp.obj[i].solidArea.contains(entity.solidPoint)){
                            if(gp.obj[i].collision == true){
                                entity.collisionOn = true;
                            }
                            if(player == true){
                                index = i;
                            }
                        }
                        break;
                    case "left":
                        entity.solidPoint.x -= entity.speed;
                        if(gp.obj[i].solidArea.contains(entity.solidPoint)){
                            if(gp.obj[i].collision == true){
                                entity.collisionOn = true;
                            }
                            if(player == true){
                                index = i;
                            }
                        }
                        break;
                    case "right":
                        entity.solidPoint.x += entity.speed;
                        if(gp.obj[i].solidArea.contains(entity.solidPoint)){
                            if(gp.obj[i].collision == true){
                                entity.collisionOn = true;
                            }
                            if(player == true){
                                index = i;
                            }
                        }
                    break;
                }
                entity.solidPoint.x = entity.solidPointDefaultX;
                entity.solidPoint.y = entity.solidPointDefaultY;
                gp.obj[i].solidArea.x = gp.obj[i].solidDefaultAreaX;
                gp.obj[i].solidArea.y = gp.obj[i].solidDefaultAreaY;

            }
        }


        return index;
    }
}
