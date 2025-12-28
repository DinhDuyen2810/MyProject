package main;

import entity.Player;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import javax.swing.JPanel;
import object.SuperObject;
import tile.FloatTile;
import tile.TileManager;

public class GamePanel extends JPanel implements Runnable{

    //SCREEN SETTINGS
    final int originalTileSize = 10;    
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
        this.setDoubleBuffered(true);
        this.addKeyListener(keyH);
        this.setFocusable(true);
    }

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
                
                //2 DRAW the screen
                repaint(); // call paintComponent
                FPSCount++;
                --delta;
            }

            if(timer >= 1000000000){
                System.out.println("FPS: " + FPSCount);
                // System.out.println("x: " + (player.worldX + player.solidPoint.x) + ", y: " + (player.worldY + player.solidPoint.y));
                timer = 0;
                FPSCount = 0;
            }
        
        }
    }

    public void update(){
        
        player.update();
    }

    public void paintComponent(Graphics g){

        super.paintComponent(g);

        Graphics2D g2 = (Graphics2D)g;

        tileM.draw(g2); 
        fTileM.draw(g2);
        for(int i = 0; i < obj.length; ++i){
            if(obj[i] != null){
                obj[i].draw(g2, this);
                obj[i].update();
            }
        }
        
        //player.draw(g2);
        ui.draw(g2);
        g2.dispose();
        
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
