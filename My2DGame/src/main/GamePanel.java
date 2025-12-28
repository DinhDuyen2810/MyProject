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
        aSetter.setObject();
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
            fTileM.draw(g2);

            for(int i = 0; i < obj.length; ++i){
                if(obj[i] != null){
                    obj[i].draw(g2, this);
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
}
