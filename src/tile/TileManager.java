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

    public final int VOID = 0, DIRT = 1, GRASS = 2, WATER = 18,
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
        loadTile(VOID, "void.png", false);
        loadTile(DIRT, "dirt.png", false);
        loadTile(GRASS, "grass.png", false);
        // Try water_still.png (animated); if not loaded, try water.png
        loadTile(WATER, "water_still.png", true);
        if (tile[WATER] == null) {
            loadTile(WATER, "water.png", true);
        }
        loadTile(SAND, "sand.png", false);
        loadTile(MAGMA, "magma.png", true);
        loadTile(FARMLAND, "farmland.png", false);
    }


    private void loadTile(int id, String file, boolean collision) {
        try {
            InputStream is = getClass().getResourceAsStream("/res/tiles/" + file);
            if (is == null) {
                System.err.println("✗ Tile file not found: " + file);
                return;
            }

            java.awt.image.BufferedImage src = ImageIO.read(is);
            if (src == null) {
                System.err.println("✗ Failed to read tile image: " + file);
                return;
            }
            
            if (file.contains("water")) {
                System.out.println("DEBUG: Loading " + file + " (w=" + src.getWidth() + ", h=" + src.getHeight() + ")");
            }

            // Attempt to create VideoTile from any reasonable spritesheet. Only use VideoTile
            // if it detects 2+ frames; otherwise treat as static image.
            VideoTile vt = VideoTile.fromSpriteSheet(src, gp.tileSize);
            if (vt != null && vt.isLoaded() && vt.getTotalFrames() >= 2) {
                if (file.contains("water")) {
                    System.out.println("✓ Water animation loaded: " + vt.getTotalFrames() + " frames");
                }
                tile[id] = vt;
                tile[id].collision = collision;
                return;
            } else if (vt != null && vt.isLoaded() && file.contains("water")) {
                System.out.println("✗ Water detected as single-frame, treating as static: " + vt.getTotalFrames() + " frames");
            }

            // Normal single-image tile: scale to gp.tileSize
            tile[id] = new Tile();
            java.awt.image.BufferedImage scaled = new java.awt.image.BufferedImage(
                gp.tileSize, gp.tileSize, java.awt.image.BufferedImage.TYPE_INT_ARGB);
            Graphics2D g = scaled.createGraphics();
            g.setRenderingHint(java.awt.RenderingHints.KEY_INTERPOLATION, 
                java.awt.RenderingHints.VALUE_INTERPOLATION_NEAREST_NEIGHBOR);
            g.drawImage(src, 0, 0, gp.tileSize, gp.tileSize, null);
            g.dispose();
            tile[id].image = scaled;
            tile[id].collision = collision;
        } catch (Exception e) {
            // ignore
        }
    }

    // ================== MAP ĐỘNG ==================
    public void update() {
        // Update any animated tiles (VideoTile)
        if (tile == null) return;
        for (int i = 0; i < tile.length; i++) {
            if (tile[i] instanceof VideoTile) {
                ((VideoTile) tile[i]).update();
            }
        }
    }

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

                    if (tileNum >= 0 && tileNum < tile.length && tile[tileNum] != null && tile[tileNum].collision) {
                        mapCollisionTile[col][row] = 1;
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void draw(Graphics2D g2) {
        int leftX = (int)Math.floor((gp.player.worldX - gp.screenWidth / 2.0) / gp.tileSize) - 3;
        int rightX = (int)Math.floor((gp.player.worldX + gp.screenWidth / 2.0) / gp.tileSize) + 3;
        int topY = (int)Math.floor((gp.player.worldY - gp.screenHeight / 2.0) / gp.tileSize) - 3;
        int botY = (int)Math.floor((gp.player.worldY + gp.screenHeight / 2.0) / gp.tileSize) + 3;

        for (int col = leftX; col <= rightX; col++) {
            for (int row = topY; row <= botY; row++) {
                if (col < 0 || row < 0 || col >= mapCols || row >= mapRows) continue;

                int tileNum = mapTileNum[col][row];
                if (tileNum < 0 || tileNum >= tile.length || tile[tileNum] == null || tile[tileNum].image == null) 
                    continue;

                double screenX = col * gp.tileSize - gp.player.worldX + gp.player.screenX;
                double screenY = row * gp.tileSize - gp.player.worldY + gp.player.screenY;

                g2.drawImage(tile[tileNum].image, (int)Math.round(screenX), (int)Math.round(screenY), 
                    gp.tileSize, gp.tileSize, null);
            }
        }
    }
}
