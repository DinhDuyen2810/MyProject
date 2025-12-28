package tile;

import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;

import javax.imageio.ImageIO;

import main.GamePanel;

public class FloatTile {

    GamePanel gp;

    public Tile[] floatTile;
    public int[][] mapfloatTileNum;
    public int[][] mapCollisionFTile;

    public int mapCols;
    public int mapRows;

    public final int NULL = 0, TREE = 1, BEDROCK = 2, MOSS_ROCK_BLOCK = 3, ROCK_BLOCK = 4, FENCE = 19, BRICK = 5;

    public FloatTile(GamePanel gp) {
        this.gp = gp;
        floatTile = new Tile[50];
        getFloatTileImage();
        loadMap("/res/maps/mapFloatTile.txt");
    }

    // ================= TILE IMAGE =================
    public void getFloatTileImage() {
        try {
            floatTile[NULL] = new Tile();

            floatTile[TREE] = new Tile();
            floatTile[TREE].image = ImageIO.read(getClass().getResourceAsStream("/res/floattiles/tree.png"));
            floatTile[TREE].collision = true;
            floatTile[TREE].normalX = 3;
            floatTile[TREE].normalY = 3;

            floatTile[BEDROCK] = new Tile();
            floatTile[BEDROCK].image = ImageIO.read(getClass().getResourceAsStream("/res/floattiles/bedrock_block_wall.png"));
            floatTile[BEDROCK].collision = true;
            floatTile[BEDROCK].normalX = 1;
            floatTile[BEDROCK].normalY = 2;

            floatTile[MOSS_ROCK_BLOCK] = new Tile();
            floatTile[MOSS_ROCK_BLOCK].image = ImageIO.read(getClass().getResourceAsStream("/res/floattiles/moss_rock_block.png"));
            floatTile[MOSS_ROCK_BLOCK].collision = true;
            floatTile[MOSS_ROCK_BLOCK].normalX = 1;
            floatTile[MOSS_ROCK_BLOCK].normalY = 2;

            floatTile[BRICK] = new Tile();
            floatTile[BRICK].image = ImageIO.read(getClass().getResourceAsStream("/res/floattiles/brick_wall.png"));
            floatTile[BRICK].collision = true;
            floatTile[BRICK].normalX = 1;
            floatTile[BRICK].normalY = 2;

            // ========== FENCE ==========
            floatTile[FENCE] = new Tile();
            floatTile[FENCE].collision = true;
            floatTile[FENCE].normalX = 1;
            floatTile[FENCE].normalY = 2;

            floatTile[FENCE].fence1  = ImageIO.read(getClass().getResourceAsStream("/res/floattiles/fence_1.png"));
            floatTile[FENCE].fence3  = ImageIO.read(getClass().getResourceAsStream("/res/floattiles/fence_3.png"));
            floatTile[FENCE].fence7  = ImageIO.read(getClass().getResourceAsStream("/res/floattiles/fence_7.png"));
            floatTile[FENCE].fence9  = ImageIO.read(getClass().getResourceAsStream("/res/floattiles/fence_9.png"));
            floatTile[FENCE].fence28 = ImageIO.read(getClass().getResourceAsStream("/res/floattiles/fence_28.png"));
            floatTile[FENCE].fence46 = ImageIO.read(getClass().getResourceAsStream("/res/floattiles/fence_46.png"));

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    // ================= LOAD MAP =================
    public void loadMap(String mapPath) {
        try {
            InputStream is = getClass().getResourceAsStream(mapPath);
            BufferedReader br = new BufferedReader(new InputStreamReader(is));

            ArrayList<String[]> lines = new ArrayList<>();
            String line;

            while ((line = br.readLine()) != null) {
                line = line.trim();
                if (line.isEmpty()) continue;
                lines.add(line.split("\\s+"));
            }
            br.close();

            mapRows = lines.size();
            mapCols = lines.get(0).length;

            mapfloatTileNum = new int[mapCols][mapRows];
            mapCollisionFTile = new int[mapCols][mapRows];

            for (int row = 0; row < mapRows; row++) {
                for (int col = 0; col < mapCols; col++) {

                    int tileNum = Integer.parseInt(lines.get(row)[col]);
                    mapfloatTileNum[col][row] = tileNum;

                    if (tileNum >= 0 &&
                        tileNum < floatTile.length &&
                        floatTile[tileNum] != null &&
                        floatTile[tileNum].collision) {

                        mapCollisionFTile[col][row] = 1;
                    }
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    // ================= FENCE AUTO TILE =================
    private BufferedImage getFenceImage(int col, int row) {

        boolean up    = row - 1 >= 0       && mapfloatTileNum[col][row - 1] == FENCE;
        boolean down  = row + 1 < mapRows  && mapfloatTileNum[col][row + 1] == FENCE;
        boolean left  = col - 1 >= 0       && mapfloatTileNum[col - 1][row] == FENCE;
        boolean right = col + 1 < mapCols  && mapfloatTileNum[col + 1][row] == FENCE;

        Tile f = floatTile[FENCE];

        if (up && down)    return f.fence46;
        if (right && down) return f.fence1;
        if (up && right)   return f.fence7;
        if (left && right) return f.fence28;
        if (left && down)  return f.fence3;
        if (left && up)    return f.fence9;

        return f.fence1;
    }

    // ================= DRAW =================
    public void draw(Graphics2D g2) {

        int worldLeftX  = (int)Math.floor((gp.player.worldX - gp.screenWidth / 2.0) / gp.tileSize) - 3;
        int worldRightX = (int)Math.floor((gp.player.worldX + gp.screenWidth / 2.0) / gp.tileSize) + 3;
        int worldTopY   = (int)Math.floor((gp.player.worldY - gp.screenHeight / 2.0) / gp.tileSize) - 3;
        int worldBotY   = (int)Math.floor((gp.player.worldY + gp.screenHeight / 2.0) / gp.tileSize) + 5;

        // Draw all float tiles that are below player
        for (int row = worldTopY; row <= worldBotY; row++) {
            for (int col = worldLeftX; col <= worldRightX; col++) {

                if (col < 0 || row < 0 || col >= mapCols || row >= mapRows) continue;

                int tileNum = mapfloatTileNum[col][row];
                if (tileNum <= 0 || tileNum >= floatTile.length) continue;

                Tile t = floatTile[tileNum];
                if (t == null) continue;

                // Only draw tiles that are below the player
                if ((row + 1) * gp.tileSize > (gp.player.worldY + gp.player.solidPoint.y)) {
                    continue;
                }

                BufferedImage imageToDraw = t.image;
                if (tileNum == FENCE) {
                    imageToDraw = getFenceImage(col, row);
                }
                if (imageToDraw == null) continue;

                double screenX = col * gp.tileSize - gp.player.worldX + gp.player.screenX;
                double screenY = row * gp.tileSize - gp.player.worldY + gp.player.screenY;

                int drawX = (int)Math.round(screenX) - (t.normalX / 2) * gp.tileSize;
                int drawY = (int)Math.round(screenY) - (t.normalY - 1) * gp.tileSize;

                g2.drawImage(
                    imageToDraw,
                    drawX,
                    drawY,
                    gp.tileSize * t.normalX,
                    gp.tileSize * t.normalY,
                    null
                );
            }
        }

        // Draw player once
        gp.player.draw(g2);

        // Draw all float tiles that are above player
        for (int row = worldTopY; row <= worldBotY; row++) {
            for (int col = worldLeftX; col <= worldRightX; col++) {

                if (col < 0 || row < 0 || col >= mapCols || row >= mapRows) continue;

                int tileNum = mapfloatTileNum[col][row];
                if (tileNum <= 0 || tileNum >= floatTile.length) continue;

                Tile t = floatTile[tileNum];
                if (t == null) continue;

                // Only draw tiles that are above the player
                if ((row + 1) * gp.tileSize <= (gp.player.worldY + gp.player.solidPoint.y)) {
                    continue;
                }

                BufferedImage imageToDraw = t.image;
                if (tileNum == FENCE) {
                    imageToDraw = getFenceImage(col, row);
                }
                if (imageToDraw == null) continue;

                double screenX = col * gp.tileSize - gp.player.worldX + gp.player.screenX;
                double screenY = row * gp.tileSize - gp.player.worldY + gp.player.screenY;

                int drawX = (int)Math.round(screenX) - (t.normalX / 2) * gp.tileSize;
                int drawY = (int)Math.round(screenY) - (t.normalY - 1) * gp.tileSize;

                g2.drawImage(
                    imageToDraw,
                    drawX,
                    drawY,
                    gp.tileSize * t.normalX,
                    gp.tileSize * t.normalY,
                    null
                );
            }
        }
    }
}
