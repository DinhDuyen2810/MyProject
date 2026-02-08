package main;

import entity.Player;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import javax.swing.JPanel;
import object.SuperObject;
import tile.FloatTile;
import tile.TileManager;
import tile.RandomDungeonMap;

public class GamePanel extends JPanel implements Runnable{
    //SCREEN SETTINGS
    final int originalTileSize = 12;    
    final int scale = 3;

    public final int tileSize = originalTileSize * scale;  // 30 x 30 pixels for 1 place
    public final int screenSize = 6;                    // need 6 or 5 

    public final int maxScreenCol = screenSize * 4;
    public final int maxScreenRow = screenSize * 3;    // to 3 x 4
    public final int screenWidth = maxScreenCol * tileSize;   // 768 pixels
    public final int screenHeight = maxScreenRow * tileSize;    // 576 pixels

    public final int maxWorldCol = 100;
    public final int maxWorldRow = 100;
    // public final int worldWidth = tileSize * maxWorldCol;
    // public final int worldHeight = tileSize * maxWorldRow;

    public int FPS = 60;
    // actual measured FPS (updated once per second)
    public int currentFPS = 0;


    // SYSTEM SETTINGS
    TileManager tileM = new TileManager(this);
    FloatTile fTileM = new FloatTile(this);
    KeyHandler keyH = new KeyHandler();
    Sound music = new Sound();
    Sound se = new Sound();

    public CollisionChecker cChecker = new CollisionChecker(this);
    public AssetSetter aSetter = new AssetSetter(this);
    public UI ui = new UI(this);
    Thread gameThread;

    // ENTITYS AND OBJECTS
    public Player player = new Player(this, keyH);
    public SuperObject obj[] = new SuperObject[100];

    // MAP STATE
    public enum MapMode { HOME, DUNGEON }
    private MapMode currentMap = MapMode.HOME;
    private int dungeonIndex = 0;
    private final int dungeonCount = 5;
    private final java.util.Random rng = new java.util.Random();
    private RandomDungeonMap.Result lastDungeon = null;
    private boolean[] dungeonVisited = null;

    public GamePanel(){

        this.setPreferredSize(new Dimension(screenWidth, screenHeight));
        this.setBackground(Color.black);
        // we'll manage our own back/front buffers for stable rendering
        this.setDoubleBuffered(false);
        this.addKeyListener(keyH);
        this.setFocusable(true);
        // use opaque RGB buffers for faster blitting (no alpha)
        backBuffer = new BufferedImage(screenWidth, screenHeight, BufferedImage.TYPE_INT_RGB);
        frontBuffer = new BufferedImage(screenWidth, screenHeight, BufferedImage.TYPE_INT_RGB);
    }

    // double buffer images and lock for swapping
    private BufferedImage backBuffer;
    private volatile BufferedImage frontBuffer;
    private final Object bufferLock = new Object();

    public void setupObjectInGame(){
        loadHomeMap();
        playMusic(0);
    }

    public void startGameThread(){

        gameThread = new Thread(this);
        gameThread.start();
    }

    @Override
    public void run() {

        double drawInterval = 1000000000 / FPS;     // sencond to nanosecond
        double delta = 0;
        long lastTime = System.nanoTime();
        long currentTime;
        long timer = 0;
        int FPSCount = 0;
        int theUpdateNum = 0;
        
        while (gameThread != null){

            currentTime = System.nanoTime();
            delta += (currentTime - lastTime) / drawInterval;
            timer += currentTime - lastTime;
            lastTime = currentTime;

            if(delta >= 1){
                //1 UPDATE information
                theUpdateNum = (theUpdateNum + 1) % 2;
                if(theUpdateNum == 1){
                }
                update();
                
                //2 DRAW the screen: render to back buffer then request repaint
                renderToBackBuffer();
                repaint(); // call paintComponent
                FPSCount++;
                --delta;
            }

            if(timer >= 1000000000){
                System.out.println("FPS: " + FPSCount);
                // expose measured FPS to UI
                currentFPS = FPSCount;
                // System.out.println("x: " + (player.worldX + player.solidPoint.x) + ", y: " + (player.worldY + player.solidPoint.y));
                timer = 0;
                FPSCount = 0;
            }
        
        }
    }

    public void update(){
        
        player.update();
        updateDungeonVisited();
        tileM.update(); // Update animation cho tiles (nước, lava, v.v.)
        for(int i = 0; i < obj.length; ++i){
            if(obj[i] != null){
                obj[i].update();
            }
        }
    }

    public void paintComponent(Graphics g){

        super.paintComponent(g);

        synchronized(bufferLock){
            if(frontBuffer != null){
                g.drawImage(frontBuffer, 0, 0, null);
            }
        }
    }

    // Render everything into backBuffer on game thread, then swap to frontBuffer
    private void renderToBackBuffer(){
        Graphics2D g2 = backBuffer.createGraphics();
        // fast pixel-art rendering hints
        g2.setRenderingHint(java.awt.RenderingHints.KEY_INTERPOLATION, java.awt.RenderingHints.VALUE_INTERPOLATION_NEAREST_NEIGHBOR);
        g2.setRenderingHint(java.awt.RenderingHints.KEY_ANTIALIASING, java.awt.RenderingHints.VALUE_ANTIALIAS_OFF);
        try{
            // clear
            g2.setColor(getBackground());
            g2.fillRect(0, 0, screenWidth, screenHeight);

            tileM.draw(g2);
            // draw float tiles/objects in depth-correct order
            fTileM.drawFirst(g2);

            for(int i = 0; i < obj.length; ++i){
                if(obj[i] != null){
                    obj[i].drawFirst(g2, this);
                }
            }

            // draw player once
            player.draw(g2);

            // draw things that should appear above player
            fTileM.drawLast(g2);

            for(int i = 0; i < obj.length; ++i){
                if(obj[i] != null){
                    obj[i].drawLast(g2, this);
                }
            }

            ui.draw(g2);
        } finally {
            g2.dispose();
        }

        // swap buffers atomically
        synchronized(bufferLock){
            BufferedImage tmp = frontBuffer;
            frontBuffer = backBuffer;
            backBuffer = tmp;
        }
    }
    public void playMusic(int i){
        music.setFile(i);
        music.play();
        music.loop();
    }
    public void stopMusic(){
        music.stop();
    }
    public void playSound(int i){
        se.setFile(i);
        se.play();
    }

    // =================== MAP CONTROL ===================
    public void onDoorEntered(){
        if (currentMap == MapMode.HOME){
            dungeonIndex = 1;
            loadDungeonMap(dungeonIndex);
        } else {
            if (dungeonIndex < dungeonCount){
                dungeonIndex++;
                loadDungeonMap(dungeonIndex);
            } else {
                loadHomeMap();
            }
        }
    }

    private void loadHomeMap(){
        currentMap = MapMode.HOME;
        lastDungeon = null;
        // reload home maps
        tileM.loadMap("/res/maps/home.txt");
        fTileM.loadMap("/res/maps/mapFloatTile.txt");
        clearObjects();
        aSetter.setObject();
        // reset player position to home spawn
        player.setDefaultValues();
    }

    private void loadDungeonMap(int index){
        currentMap = MapMode.DUNGEON;
        clearObjects();

        // generate random dungeon layout
        int roomCount = 6 + rng.nextInt(4); // 6-9 rooms
        RandomDungeonMap.Result result = RandomDungeonMap.generate(
            maxWorldCol, maxWorldRow, roomCount, rng
        );
        lastDungeon = result;
        dungeonVisited = new boolean[result.rooms != null ? result.rooms.size() : 0];

        // load generated tile map (void is collidable)
        tileM.loadMapFromArray(result.mapTiles, true);
        // load generated float tiles (bedrock border)
        fTileM.loadMapFromArray(result.mapFloatTiles);

        // place door at end room
        object.OBJ_Door door = new object.OBJ_Door();
        door.worldX = result.endX * tileSize;
        door.worldY = result.endY * tileSize;
        obj[0] = door;

        // move player to start room center
        player.worldX = result.startX * tileSize;
        player.worldY = result.startY * tileSize;
        updateDungeonVisited();
    }

    public RandomDungeonMap.Result getDungeonMap(){
        return currentMap == MapMode.DUNGEON ? lastDungeon : null;
    }

    public boolean[] getDungeonVisited(){
        return currentMap == MapMode.DUNGEON ? dungeonVisited : null;
    }

    private void updateDungeonVisited(){
        if (currentMap != MapMode.DUNGEON || lastDungeon == null || lastDungeon.rooms == null) return;
        if (dungeonVisited == null || dungeonVisited.length != lastDungeon.rooms.size()) return;

        int playerTileX = (int)Math.round(player.worldX / tileSize);
        int playerTileY = (int)Math.round(player.worldY / tileSize);

        for (int i = 0; i < lastDungeon.rooms.size(); i++){
            tile.RandomDungeonMap.RoomInfo r = lastDungeon.rooms.get(i);
            if (playerTileX >= r.x && playerTileX < r.x + r.w &&
                playerTileY >= r.y && playerTileY < r.y + r.h) {
                dungeonVisited[i] = true;
                break;
            }
        }
    }

    private void clearObjects(){
        for (int i = 0; i < obj.length; i++){
            obj[i] = null;
        }
    }

}
