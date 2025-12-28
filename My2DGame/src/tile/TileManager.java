package tile;

import java.awt.Graphics2D;
import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

import javax.imageio.ImageIO;

import main.GamePanel;

public class TileManager {

    public final int VOID = 0, DIRT = 1, GRASS = 2, WATER = 3,
                     LAVA = 4, SAND = 5, MAGMA = 6, FARMLAND = 17;

    GamePanel gp;
    public Tile[] tile;

    public int mapCols;
    public int mapRows;

    public int[][] mapTileNum;
    public int[][] mapCollisionTile;

    public TileManager(GamePanel gp) {
        this.gp = gp;

        tile = new Tile[30]; 

        getTileImage();
        loadMap("/res/maps/home.txt");
    }

    public void getTileImage() {
        try {
            loadTile(VOID, "void.png", false);
            loadTile(DIRT, "dirt.png", false);
            loadTile(GRASS, "grass.png", false);
            loadTile(WATER, "water.png", true);
            //loadTile(LAVA, "lava.png", true);
            loadTile(SAND, "sand.png", false);
            loadTile(MAGMA, "magma.png", true);
            loadTile(FARMLAND, "farmland.png", false);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void loadTile(int id, String file, boolean collision) {
        try {
            InputStream is = getClass().getResourceAsStream("/res/tiles/" + file);
            if (is == null) return;

            tile[id] = new Tile();
            // load original image then pre-scale to tileSize to avoid per-frame scaling
            java.awt.image.BufferedImage src = ImageIO.read(is);
            if (src != null) {
                java.awt.image.BufferedImage scaled = new java.awt.image.BufferedImage(gp.tileSize, gp.tileSize, java.awt.image.BufferedImage.TYPE_INT_ARGB);
                Graphics2D g = scaled.createGraphics();
                g.setRenderingHint(java.awt.RenderingHints.KEY_INTERPOLATION, java.awt.RenderingHints.VALUE_INTERPOLATION_NEAREST_NEIGHBOR);
                g.drawImage(src, 0, 0, gp.tileSize, gp.tileSize, null);
                g.dispose();
                tile[id].image = scaled;
            } else {
                tile[id].image = null;
            }
            tile[id].collision = collision;

        } catch (Exception e) {
            // nuốt lỗi
        }
    }

    // ================== MAP ĐỘNG ==================
    public void loadMap(String mapPath) {
        try {
            InputStream is = getClass().getResourceAsStream(mapPath);
            BufferedReader br = new BufferedReader(new InputStreamReader(is));

            List<String[]> lines = new ArrayList<>();
            String line;

            while ((line = br.readLine()) != null) {
                line = line.trim();
                if (line.isEmpty()) continue;

                lines.add(line.split("\\s+"));
            }
            br.close();

            mapRows = lines.size();
            mapCols = lines.get(0).length;

            mapTileNum = new int[mapCols][mapRows];
            mapCollisionTile = new int[mapCols][mapRows];

            for (int row = 0; row < mapRows; row++) {
                for (int col = 0; col < mapCols; col++) {

                    int tileNum = Integer.parseInt(lines.get(row)[col]);
                    mapTileNum[col][row] = tileNum;

                    if (tileNum >= 0 &&
                        tileNum < tile.length &&
                        tile[tileNum] != null &&
                        tile[tileNum].collision) {
                        mapCollisionTile[col][row] = 1;
                    }
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    // ================== DRAW ==================
    public void draw(Graphics2D g2) {

        int worldLeftX  = (int)Math.floor((gp.player.worldX - gp.screenWidth / 2.0) / gp.tileSize) - 3;
        int worldRightX = (int)Math.floor((gp.player.worldX + gp.screenWidth / 2.0) / gp.tileSize) + 3;
        int worldTopY   = (int)Math.floor((gp.player.worldY - gp.screenHeight / 2.0) / gp.tileSize) - 3;
        int worldBotY   = (int)Math.floor((gp.player.worldY + gp.screenHeight / 2.0) / gp.tileSize) + 3;

        for (int col = worldLeftX; col <= worldRightX; col++) {
            for (int row = worldTopY; row <= worldBotY; row++) {

                if (col < 0 || row < 0 || col >= mapCols || row >= mapRows)
                    continue;

                int tileNum = mapTileNum[col][row];

                if (tileNum < 0 || tileNum >= tile.length) continue;
                if (tile[tileNum] == null) continue;
                if (tile[tileNum].image == null) continue;

                double screenX = col * gp.tileSize - gp.player.worldX + gp.player.screenX;
                double screenY = row * gp.tileSize - gp.player.worldY + gp.player.screenY;

                g2.drawImage(
                        tile[tileNum].image,
                        (int)Math.round(screenX),
                        (int)Math.round(screenY),
                        gp.tileSize,
                        gp.tileSize,
                        null
                );
            }
        }
    }
}
