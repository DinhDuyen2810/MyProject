Main.java
    package main; // Khai báo package chứa lớp Main, giúp tổ chức mã nguồn theo thư mục logic
    import javax.swing.JFrame; // Import lớp JFrame để tạo cửa sổ giao diện (GUI) trong Java Swing
    public class Main {
        public static void main(String[] args) { // Hàm main() – điểm bắt đầu chương trình
            JFrame window = new JFrame(); // Tạo một đối tượng JFrame – cửa sổ chính của game
            window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // Khi người chơi nhấn nút "X", chương trình sẽ thoát hoàn toàn
            window.setResizable(false); // Không cho phép người dùng thay đổi kích thước cửa sổ (giữ tỉ lệ khung hình cố định)
            window.setTitle("Minecraft"); // Đặt tiêu đề cho cửa sổ game hiển thị trên thanh tiêu đề (title bar)
            GamePanel gamePanel = new GamePanel(); // Tạo đối tượng GamePanel – lớp này chứa logic game, vẽ đồ họa và xử lý cập nhật khung hình
            window.add(gamePanel); // Thêm GamePanel vào cửa sổ JFrame để hiển thị nội dung game
            window.pack(); // Tự động điều chỉnh kích thước cửa sổ sao cho vừa khít với kích thước của GamePanel
            window.setLocationRelativeTo(null); // Đặt vị trí cửa sổ ở giữa màn hình (null = giữa màn hình)
            window.setVisible(true); // Hiển thị cửa sổ game lên màn hình (mặc định JFrame ẩn khi mới tạo)
            gamePanel.setupObjectInGame(); // Gọi hàm khởi tạo các đối tượng trong game (ví dụ: người chơi, vật thể, bản đồ, v.v.)
            gamePanel.startGameThread(); // Bắt đầu luồng game (game loop), nơi vẽ khung hình và cập nhật logic game liên tục
        }
    }

KeyHandler.Java

    package main; // Khai báo package chứa lớp KeyHandler
    import java.awt.event.KeyEvent; // Import lớp KeyEvent để nhận mã phím (key code)
    import java.awt.event.KeyListener; // Import interface KeyListener để lắng nghe sự kiện bàn phím
    public class KeyHandler implements KeyListener { // Lớp KeyHandler triển khai KeyListener để xử lý phím
        public boolean isUpPressed, isDownPressed, isLeftPressed, isRightPressed; // Các biến cờ (flag) lưu trạng thái phím đang nhấn
        @Override
        public void keyTyped(KeyEvent e) { // Hàm bắt sự kiện khi người dùng gõ ký tự (ít dùng trong game)
        }
        @Override
        public void keyPressed(KeyEvent e) { // Hàm gọi khi người dùng NHẤN phím
            int code = e.getKeyCode(); // Lấy mã phím người dùng nhấn
            switch (code) { // Kiểm tra phím được nhấn
                case KeyEvent.VK_W: case KeyEvent.VK_UP: // Nếu nhấn W hoặc phím mũi tên lên
                    isUpPressed = true; // Đặt cờ di chuyển lên là true
                    break;
                case KeyEvent.VK_S: case KeyEvent.VK_DOWN: // Nếu nhấn S hoặc phím mũi tên xuống
                    isDownPressed = true; // Đặt cờ di chuyển xuống là true
                    break;
                case KeyEvent.VK_A: case KeyEvent.VK_LEFT: // Nếu nhấn A hoặc phím mũi tên trái
                    isLeftPressed = true; // Đặt cờ di chuyển trái là true
                    break;
                case KeyEvent.VK_D: case KeyEvent.VK_RIGHT: // Nếu nhấn D hoặc phím mũi tên phải
                    isRightPressed = true; // Đặt cờ di chuyển phải là true
                    break;
            }
        }
        @Override
        public void keyReleased(KeyEvent e) { // Hàm gọi khi người dùng NHẢ phím
            int code = e.getKeyCode(); // Lấy mã phím người dùng nhả ra
            switch (code) { // Kiểm tra phím được nhả
                case KeyEvent.VK_W: case KeyEvent.VK_UP: // Nếu nhả W hoặc phím mũi tên lên
                    isUpPressed = false; // Đặt cờ di chuyển lên là false
                    break;
                case KeyEvent.VK_S: case KeyEvent.VK_DOWN: // Nếu nhả S hoặc phím mũi tên xuống
                    isDownPressed = false; // Đặt cờ di chuyển xuống là false
                    break;
                case KeyEvent.VK_A: case KeyEvent.VK_LEFT: // Nếu nhả A hoặc phím mũi tên trái
                    isLeftPressed = false; // Đặt cờ di chuyển trái là false
                    break;
                case KeyEvent.VK_D: case KeyEvent.VK_RIGHT: // Nếu nhả D hoặc phím mũi tên phải
                    isRightPressed = false; // Đặt cờ di chuyển phải là false
                    break;
            }
        }
    }

GamePanel.java

    package main; // Package chứa lớp GamePanel

    import java.awt.Color; // Dùng để đặt màu nền
    import java.awt.Dimension; // Dùng để thiết lập kích thước JPanel
    import java.awt.Graphics; // Dùng để vẽ hình
    import java.awt.Graphics2D; // Dùng để vẽ 2D nâng cao
    import javax.swing.JPanel; // JPanel là lớp cơ sở hiển thị đồ họa trong Swing
    import entity.Player; // Import lớp Player
    import object.SuperObject; // Import lớp cha của tất cả vật thể (item, chest, key,...)
    import tile.FloatTile; // Import lớp xử lý hiệu ứng vật thể nổi
    import tile.TileManager; // Import lớp quản lý tile map (bản đồ ô vuông)

    public class GamePanel extends JPanel implements Runnable { // Lớp chính hiển thị và điều khiển game

        // ===== THIẾT LẬP MÀN HÌNH =====
        final int originalTileSize = 10; // Kích thước gốc của 1 tile (ô vuông)
        final int scale = 3; // Tỷ lệ phóng to tile (10 * 3 = 30px)
        public final int tileSize = originalTileSize * scale; // Kích thước thật của 1 tile = 30px
        public final int screenSize = 5; // Số ô cơ sở trên mỗi vùng nhỏ (5x5 hoặc 6x6 tùy map)
        public final int maxScreenCol = screenSize * 4; // Số cột tổng (5 * 4 = 20 cột)
        public final int maxScreenRow = screenSize * 3; // Số hàng tổng (5 * 3 = 15 hàng)
        public final int screenWidth = maxScreenCol * tileSize; // Chiều rộng màn hình = 20 * 30 = 600px
        public final int screenHeight = maxScreenRow * tileSize; // Chiều cao màn hình = 15 * 30 = 450px
        public final int maxWorldCol = 100; // Số cột tối đa của thế giới (map lớn)
        public final int maxWorldRow = 100; // Số hàng tối đa của thế giới
        public int FPS = 60; // Giới hạn tốc độ khung hình (60 FPS)

        // ===== CÁC THÀNH PHẦN HỆ THỐNG =====
        TileManager tileM = new TileManager(this); // Quản lý tile map tĩnh (nền, tường, đường,...)
        FloatTile fTileM = new FloatTile(this); // Quản lý tile động (hiệu ứng nổi)
        KeyHandler keyH = new KeyHandler(); // Bắt sự kiện bàn phím
        Sound music = new Sound(); // Phát nhạc nền
        Sound se = new Sound(); // Phát hiệu ứng âm thanh (sound effect)
        public CollisionChecker cChecker = new CollisionChecker(this); // Kiểm tra va chạm giữa đối tượng
        public AssetSetter aSetter = new AssetSetter(this); // Dùng để đặt đối tượng (item, cửa,...)
        public UI ui = new UI(this); // Quản lý giao diện người chơi (máu, điểm,...)
        Thread gameThread; // Luồng chính chạy game loop

        // ===== THỰC THỂ (ENTITY) & VẬT THỂ (OBJECT) =====
        public Player player = new Player(this, keyH); // Tạo đối tượng người chơi
        public SuperObject obj[] = new SuperObject[10]; // Mảng chứa tối đa 10 vật thể (chìa khóa, rương, cửa,...)

        public GamePanel() { // Hàm khởi tạo GamePanel
            this.setPreferredSize(new Dimension(screenWidth, screenHeight)); // Thiết lập kích thước khung chơi
            this.setBackground(Color.black); // Đặt màu nền đen
            this.setDoubleBuffered(true); // Bật double buffering để vẽ mượt hơn, tránh giật hình
            this.addKeyListener(keyH); // Gắn bộ lắng nghe phím
            this.setFocusable(true); // Cho phép JPanel nhận sự kiện bàn phím
        }

        public void setupObjectInGame() { // Hàm khởi tạo vật thể khi bắt đầu game
            aSetter.setObject(); // Đặt các vật thể vào bản đồ
            playMusic(0); // Phát nhạc nền
        }

        public void startGameThread() { // Bắt đầu luồng game
            gameThread = new Thread(this); // Tạo luồng mới từ Runnable GamePanel
            gameThread.start(); // Chạy luồng game
        }

        @Override
        public void run() { // Game loop chính của trò chơi
            double drawInterval = 1000000000 / FPS; // Khoảng thời gian giữa 2 frame (đơn vị nano giây)
            double delta = 0; // Biến xác định khi nào cần cập nhật và vẽ frame
            long lastTime = System.nanoTime(); // Thời gian trước đó
            long currentTime; // Thời gian hiện tại
            long timer = 0; // Đếm thời gian để tính FPS thực tế
            int FPSCount = 0; // Đếm số khung hình trong 1 giây
            int theUpdateNum = 0; // Biến phụ dùng kiểm soát số lần update (nếu cần)

            while (gameThread != null) { // Vòng lặp chạy liên tục cho đến khi dừng game
                currentTime = System.nanoTime(); // Lấy thời gian hiện tại
                delta += (currentTime - lastTime) / drawInterval; // Tính khoảng thời gian tích lũy
                timer += currentTime - lastTime; // Cộng dồn thời gian để đo FPS
                lastTime = currentTime; // Cập nhật mốc thời gian

                if (delta >= 1) { // Nếu đã đến lúc cập nhật frame mới
                    theUpdateNum = (theUpdateNum + 1) % 2; // Biến phụ (chỉ dùng để debug hoặc điều chỉnh)
                    if (theUpdateNum == 1) { } // Không làm gì, chỉ ví dụ
                    update(); // Cập nhật logic game (nhân vật, va chạm, hiệu ứng,...)
                    repaint(); // Gọi paintComponent() để vẽ lại màn hình
                    FPSCount++; // Tăng bộ đếm FPS
                    --delta; // Giảm delta sau khi đã vẽ xong 1 frame
                }

                if (timer >= 1000000000) { // Nếu đã qua 1 giây
                    System.out.println("FPS: " + FPSCount); // In FPS thực tế ra console
                    timer = 0; // Reset bộ đếm thời gian
                    FPSCount = 0; // Reset bộ đếm FPS
                }
            }
        }

        public void update() { // Cập nhật logic game mỗi khung hình
            player.update(); // Cập nhật trạng thái và vị trí của người chơi
        }

        public void paintComponent(Graphics g) { // Hàm vẽ lại mọi thứ trên màn hình
            super.paintComponent(g); // Xóa frame cũ
            Graphics2D g2 = (Graphics2D) g; // Ép kiểu sang Graphics2D để vẽ nâng cao
            tileM.draw(g2); // Vẽ bản đồ nền (ground tiles)
            for (int i = 0; i < obj.length; ++i) { // Lặp qua tất cả vật thể trong mảng
                if (obj[i] != null) { // Nếu vật thể tồn tại
                    obj[i].draw(g2, this); // Vẽ vật thể đó
                }
            }
            fTileM.draw(g2); // Vẽ các tile nổi (nước, hiệu ứng,...)
            //player.draw(g2); // Vẽ người chơi (tạm thời bị tắt)
            ui.draw(g2); // Vẽ giao diện người chơi (UI)
            g2.dispose(); // Giải phóng tài nguyên vẽ sau khi hoàn tất
        }

        public void playMusic(int i) { // Phát nhạc nền
            music.setFile(i); // Chọn file nhạc theo chỉ số
            music.play(); // Bắt đầu phát
            music.loop(); // Lặp vô hạn
        }

        public void stopMusic() { // Dừng nhạc nền
            music.stop();
        }

        public void playSound(int i) { // Phát âm thanh hiệu ứng (sound effect)
            se.setFile(i); // Chọn file âm thanh
            se.play(); // Phát một lần
        }
    }

CollisionChecker.java

    package main; // Khai báo package chứa lớp này

    import entity.Entity; // Import lớp Entity từ package entity

    public class CollisionChecker { // Lớp kiểm tra va chạm giữa Entity và bản đồ hoặc vật thể
        GamePanel gp; // Tham chiếu đến GamePanel để truy cập dữ liệu bản đồ, vật thể, v.v.

        public CollisionChecker(GamePanel gp){ // Hàm khởi tạo, nhận tham chiếu GamePanel
            this.gp = gp; // Lưu tham chiếu vào biến gp
        }

        public void checkTile(Entity entity){ // Hàm kiểm tra va chạm giữa entity và tile (ô vuông bản đồ)
            double entityX = (entity.worldX + entity.solidPoint.x) / gp.tileSize; // Tính vị trí X theo ô (tile)
            double entityY = (entity.worldY + entity.solidPoint.y) / gp.tileSize; // Tính vị trí Y theo ô (tile)
            int tile1Check, tile2Check; // Hai ô cần kiểm tra va chạm theo hướng di chuyển
            int floatTile1Check, floatTile2Check; // Hai ô trên layer “float tile” (nếu có)

            switch(entity.direction){ // Xét hướng di chuyển của entity
                case "up": // Khi đi lên
                    tile1Check = gp.tileM.mapCollisionTile[(int)entityX][(int)(entityY - 4 * entity.speed / gp.tileSize)]; // Lấy tile phía trên
                    tile2Check = gp.tileM.mapCollisionTile[(int)entityX][(int)(entityY - 4 * entity.speed / gp.tileSize)]; // Tile phụ
                    floatTile1Check = gp.fTileM.mapCollisionFTile[(int)entityX][(int)(entityY - 4 * entity.speed / gp.tileSize)]; // Float tile chính
                    floatTile2Check = gp.fTileM.mapCollisionFTile[(int)entityX][(int)(entityY - 4 * entity.speed / gp.tileSize)]; // Float tile phụ
                    if(entityX - (int)(entityX) > 0.6){ // Nếu entity lệch phải so với tile
                        tile2Check = gp.tileM.mapCollisionTile[(int)entityX + 1][(int)(entityY - 4 * entity.speed / gp.tileSize)]; // Kiểm tra thêm tile bên phải
                        floatTile2Check = gp.fTileM.mapCollisionFTile[(int)entityX + 1][(int)(entityY - 4 * entity.speed / gp.tileSize)];
                    } else if(entityX - (int)(entityX) < 0.4) { // Nếu lệch trái
                        tile2Check = gp.tileM.mapCollisionTile[(int)entityX - 1][(int)(entityY - 4 * entity.speed / gp.tileSize)]; // Kiểm tra tile bên trái
                        floatTile2Check = gp.fTileM.mapCollisionFTile[(int)entityX - 1][(int)(entityY - 4 * entity.speed / gp.tileSize)];
                    }
                    if(tile1Check == 1 || tile2Check == 1 || floatTile1Check == 1 || floatTile2Check == 1){ // Nếu gặp tile có collision
                        entity.collisionOn = true; // Bật cờ va chạm
                    }
                    break;

                case "down": // Khi đi xuống
                    tile1Check = gp.tileM.mapCollisionTile[(int)entityX][(int)(entityY + 4 * entity.speed / gp.tileSize)];
                    tile2Check = gp.tileM.mapCollisionTile[(int)entityX][(int)(entityY + 4 * entity.speed / gp.tileSize)];
                    floatTile1Check = gp.fTileM.mapCollisionFTile[(int)entityX][(int)(entityY + 4 * entity.speed / gp.tileSize)];
                    floatTile2Check = gp.fTileM.mapCollisionFTile[(int)entityX][(int)(entityY + 4 * entity.speed / gp.tileSize)];
                    if(entityX - (int)(entityX) > 0.6){
                        tile2Check = gp.tileM.mapCollisionTile[(int)entityX + 1][(int)(entityY + 4 * entity.speed / gp.tileSize)];
                        floatTile2Check = gp.fTileM.mapCollisionFTile[(int)entityX + 1][(int)(entityY + 4 * entity.speed / gp.tileSize)];
                    } else if(entityX - (int)(entityX) < 0.4) {
                        tile2Check = gp.tileM.mapCollisionTile[(int)entityX - 1][(int)(entityY + 4 * entity.speed / gp.tileSize)];
                        floatTile2Check = gp.fTileM.mapCollisionFTile[(int)entityX - 1][(int)(entityY + 4 * entity.speed / gp.tileSize)];
                    }
                    if(tile1Check == 1 || tile2Check == 1 || floatTile1Check == 1 || floatTile2Check == 1){
                        entity.collisionOn = true;
                    }
                    break;

                case "left": // Khi đi sang trái
                    tile1Check = gp.tileM.mapCollisionTile[(int)(entityX - 8 * entity.speed / gp.tileSize)][(int)entityY];
                    tile2Check = gp.tileM.mapCollisionTile[(int)(entityX - 8 * entity.speed / gp.tileSize)][(int)entityY];
                    floatTile1Check = gp.fTileM.mapCollisionFTile[(int)(entityX - 8 * entity.speed / gp.tileSize)][(int)entityY];
                    floatTile2Check = gp.fTileM.mapCollisionFTile[(int)(entityX - 8 * entity.speed / gp.tileSize)][(int)entityY];
                    if(entityY - (int)(entityY) > 0.9){ // Nếu entity lệch xuống so với tile
                        tile2Check = gp.tileM.mapCollisionTile[(int)(entityX - entity.speed / gp.tileSize)][(int)entityY + 1];
                        floatTile2Check = gp.fTileM.mapCollisionFTile[(int)(entityX - entity.speed / gp.tileSize)][(int)entityY + 1];
                    } else if(entityY - (int)(entityY) < 0.1) { // Nếu lệch lên
                        tile2Check = gp.tileM.mapCollisionTile[(int)(entityX - entity.speed / gp.tileSize)][(int)entityY - 1];
                        floatTile2Check = gp.fTileM.mapCollisionFTile[(int)(entityX - entity.speed / gp.tileSize)][(int)entityY - 1];
                    }
                    if(tile1Check == 1 || tile2Check == 1 || floatTile1Check == 1 || floatTile2Check == 1){
                        entity.collisionOn = true;
                    }
                    break;

                case "right": // Khi đi sang phải
                    tile1Check = gp.tileM.mapCollisionTile[(int)(entityX + 8 * entity.speed / gp.tileSize)][(int)entityY];
                    tile2Check = gp.tileM.mapCollisionTile[(int)(entityX + 8 * entity.speed / gp.tileSize)][(int)entityY];
                    floatTile1Check = gp.fTileM.mapCollisionFTile[(int)(entityX + 8 * entity.speed / gp.tileSize)][(int)entityY];
                    floatTile2Check = gp.fTileM.mapCollisionFTile[(int)(entityX + 8 * entity.speed / gp.tileSize)][(int)entityY];
                    if(entityY - (int)(entityY) > 0.9){
                        tile2Check = gp.tileM.mapCollisionTile[(int)(entityX - entity.speed / gp.tileSize)][(int)entityY + 1];
                        floatTile2Check = gp.fTileM.mapCollisionFTile[(int)(entityX - entity.speed / gp.tileSize)][(int)entityY + 1];
                    } else if(entityY - (int)(entityY) < 0.1) {
                        tile2Check = gp.tileM.mapCollisionTile[(int)(entityX - entity.speed / gp.tileSize)][(int)entityY - 1];
                        floatTile2Check = gp.fTileM.mapCollisionFTile[(int)(entityX - entity.speed / gp.tileSize)][(int)entityY - 1];
                    }
                    if(tile1Check == 1 || tile2Check == 1 || floatTile1Check == 1 || floatTile2Check == 1){
                        entity.collisionOn = true;
                    }
                    break;
            }
        }

        public int checkObject(Entity entity, boolean player){ // Kiểm tra va chạm giữa entity và vật thể (object)
            int index = 999; // Biến lưu vị trí object bị va chạm (999 = không có)
            for(int i = 0; i < gp.obj.length; i++){ // Duyệt qua tất cả vật thể
                if(gp.obj[i] != null){ // Nếu vật thể tồn tại
                    entity.solidPoint.x = (int)(entity.worldX + entity.solidPoint.x); // Xác định điểm va chạm X
                    entity.solidPoint.y = (int)(entity.worldY + entity.solidPoint.y); // Xác định điểm va chạm Y
                    gp.obj[i].solidArea.x = gp.obj[i].worldX + gp.obj[i].solidArea.x - (gp.obj[i].normalX / 2) * gp.tileSize; // Cập nhật vùng va chạm X của object
                    gp.obj[i].solidArea.y = gp.obj[i].worldY + gp.obj[i].solidArea.y - (gp.obj[i].normalY - 1) * gp.tileSize; // Cập nhật vùng va chạm Y

                    switch(entity.direction){ // Xét hướng di chuyển để kiểm tra va chạm
                        case "up":
                            entity.solidPoint.y -= entity.speed; // Di chuyển điểm va chạm lên
                            if(gp.obj[i].solidArea.contains(entity.solidPoint)){ // Nếu chạm vùng va chạm
                                if(gp.obj[i].collision == true){ // Nếu object có collision
                                    entity.collisionOn = true; // Bật cờ va chạm
                                }
                                if(player == true){ // Nếu là player
                                    index = i; // Ghi lại chỉ số object
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
                    entity.solidPoint.x = entity.solidPointDefaultX; // Reset lại vị trí gốc của điểm va chạm
                    entity.solidPoint.y = entity.solidPointDefaultY;
                    gp.obj[i].solidArea.x = gp.obj[i].solidDefaultAreaX; // Reset vùng va chạm object
                    gp.obj[i].solidArea.y = gp.obj[i].solidDefaultAreaY;
                }
            }
            return index; // Trả về chỉ số object bị va chạm (nếu có)
        }
    }

AssatSetter.java

    package main; // Khai báo package chứa lớp AssetSetter

    import object.OBJ_Bed; // Import class OBJ_Bed
    import object.OBJ_Chest; // Import class OBJ_Chest
    import object.OBJ_CraftBlock; // Import class OBJ_CraftBlock
    import object.OBJ_Diamond; // Import class OBJ_Diamond
    import object.OBJ_Door; // Import class OBJ_Door
    import object.OBJ_EnchangeTable; // Import class OBJ_EnchangeTable
    import object.OBJ_Furnace; // Import class OBJ_Furnace

    public class AssetSetter { // Lớp chịu trách nhiệm đặt các vật thể (object) vào bản đồ
        GamePanel gp; // Biến tham chiếu đến GamePanel để truy cập dữ liệu trò chơi

        public AssetSetter(GamePanel gp){ // Hàm khởi tạo nhận tham chiếu GamePanel
            this.gp = gp; // Lưu tham chiếu GamePanel
        }

        public void setObject(){ // Hàm đặt tất cả vật thể (object) trong game
            gp.obj[0] = new OBJ_Diamond(); // Tạo vật thể Kim cương
            gp.obj[0].worldX = 25 * gp.tileSize; // Đặt vị trí X của Kim cương
            gp.obj[0].worldY = 23 * gp.tileSize; // Đặt vị trí Y của Kim cương

            gp.obj[1] = new OBJ_Door(); // Tạo vật thể Cửa
            gp.obj[1].worldX = 25 * gp.tileSize; // Đặt vị trí X của Cửa
            gp.obj[1].worldY = 20 * gp.tileSize; // Đặt vị trí Y của Cửa
            
            gp.obj[2] = new OBJ_Chest(); // Tạo vật thể Rương
            gp.obj[2].worldX = 35 * gp.tileSize; // Đặt vị trí X của Rương
            gp.obj[2].worldY = 23 * gp.tileSize; // Đặt vị trí Y của Rương
            
            gp.obj[3] = new OBJ_Bed(); // Tạo vật thể Giường
            gp.obj[3].worldX = 32 * gp.tileSize; // Đặt vị trí X của Giường
            gp.obj[3].worldY = 23 * gp.tileSize; // Đặt vị trí Y của Giường
            
            gp.obj[4] = new OBJ_CraftBlock(); // Tạo vật thể Bàn chế tạo
            gp.obj[4].worldX = 29 * gp.tileSize; // Đặt vị trí X của Bàn chế tạo
            gp.obj[4].worldY = 23 * gp.tileSize; // Đặt vị trí Y của Bàn chế tạo
            
            gp.obj[5] = new OBJ_Furnace(); // Tạo vật thể Lò nung
            gp.obj[5].worldX = 28 * gp.tileSize; // Đặt vị trí X của Lò nung
            gp.obj[5].worldY = 23 * gp.tileSize; // Đặt vị trí Y của Lò nung
            
            gp.obj[6] = new OBJ_EnchangeTable(); // Tạo vật thể Bàn phù phép
            gp.obj[6].worldX = 27 * gp.tileSize; // Đặt vị trí X của Bàn phù phép
            gp.obj[6].worldY = 23 * gp.tileSize; // Đặt vị trí Y của Bàn phù phép

            gp.obj[7] = new OBJ_Diamond(); // Tạo viên Kim cương thứ hai
            gp.obj[7].worldX = 15 * gp.tileSize; // Đặt vị trí X của viên này
            gp.obj[7].worldY = 26 * gp.tileSize; // Đặt vị trí Y của viên này

            gp.obj[8] = new OBJ_Diamond(); // Tạo viên Kim cương thứ ba
            gp.obj[8].worldX = 28 * gp.tileSize; // Đặt vị trí X
            gp.obj[8].worldY = 28 * gp.tileSize; // Đặt vị trí Y
        }
    }

Sound.java

    package main;
    import java.net.URL;
    import javax.sound.sampled.AudioInputStream;
    import javax.sound.sampled.AudioSystem;
    import javax.sound.sampled.Clip;

    public class Sound {
        Clip clip; // Đối tượng dùng để phát âm thanh
        URL soundURL[] = new URL[30]; // Mảng lưu đường dẫn các file âm thanh

        // Constructor: nạp các file âm thanh cần thiết vào mảng soundURL
        public Sound() {
            soundURL[0] = getClass().getResource("/res/sound/Minecraft_Volume_Alpha.wav"); // Nhạc nền
            soundURL[1] = getClass().getResource("/res/sound/Wooden_Door_open.wav");       // Âm thanh mở cửa
        }

        // Chuẩn bị file âm thanh theo chỉ số i
        public void setFile(int i) {
            try {
                AudioInputStream ais = AudioSystem.getAudioInputStream(soundURL[i]); // Đọc dữ liệu âm thanh
                clip = AudioSystem.getClip(); // Tạo clip âm thanh
                clip.open(ais); // Mở và nạp âm thanh vào clip
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        // Phát âm thanh 1 lần
        public void play() {
            clip.start();
        }

        // Phát lặp liên tục (dùng cho nhạc nền)
        public void loop() {
            clip.loop(Clip.LOOP_CONTINUOUSLY);
        }

        // Dừng phát âm thanh
        public void stop() {
            clip.stop();
        }
    }

UI.java

    package main;
    import java.awt.Color;
    import java.awt.Font;
    import java.awt.Graphics2D;
    import java.awt.image.BufferedImage;
    import object.OBJ_Diamond;

    public class UI {
        GamePanel gp; // Tham chiếu đến GamePanel để truy cập dữ liệu game (như FPS, player, tileSize)
        Font arial_20; // Font chữ hiển thị text trong game
        BufferedImage diamondImage; // Ảnh biểu tượng kim cương (hiển thị số lượng người chơi thu thập)
        public boolean messageOn = false; // Biến kiểm soát việc hiển thị thông báo
        public String message = ""; // Chuỗi thông báo cần hiển thị
        int counter = 0; // Bộ đếm thời gian hiển thị thông báo

        // Hàm khởi tạo UI, truyền vào tham chiếu GamePanel
        public UI(GamePanel gp) {
            this.gp = gp; // Gán tham chiếu để dùng trong class này
            arial_20 = new Font("Arial", Font.PLAIN, 20); // Chọn font Arial cỡ 20
            OBJ_Diamond diamond = new OBJ_Diamond(); // Tạo tạm đối tượng kim cương để lấy hình ảnh
            diamondImage = diamond.image; // Lưu hình kim cương vào biến diamondImage
        }

        // Phương thức hiển thị thông báo trên màn hình (kích hoạt cờ messageOn)
        public void showMessage(String message) {
            this.message = message; // Gán nội dung thông báo
            messageOn = true; // Bật trạng thái hiển thị
        }

        // Vẽ UI lên màn hình (được gọi trong GamePanel)
        public void draw(Graphics2D g2) {
            g2.setFont(arial_20); // Cài font chữ
            g2.setColor(Color.WHITE); // Màu chữ trắng

            // Hiển thị FPS ở góc trái trên cùng
            g2.drawString("FPS: " + gp.FPS, 10, 20);

            // Hiển thị tọa độ thực tế của người chơi (worldX + offset từ solidPoint)
            g2.drawString("x: " + (gp.player.worldX + gp.player.solidPoint.x) + "  y: "
                    + (gp.player.worldY + gp.player.solidPoint.y), 10, 40);

            // Hiển thị hình kim cương và số lượng người chơi thu thập được
            g2.drawImage(diamondImage, 10, 50, gp.tileSize, gp.tileSize, null);
            g2.drawString("x " + gp.player.hasDiamond, 40, 73);

            // Nếu đang bật hiển thị message (ví dụ: “You got a diamond!”)
            if (messageOn) {
                g2.drawString(message, 10, 100); // Vẽ thông báo lên màn hình
                counter++; // Tăng bộ đếm mỗi khung hình

                // Sau 1 giây (counter > FPS), tắt thông báo
                if (counter > gp.FPS) {
                    messageOn = false;
                    counter = 0;
                }
            }
        }
    }

Entity.java

    package entity;

    import java.awt.Point;
    import java.awt.image.BufferedImage;

    // Lớp cha (base class) cho tất cả thực thể (entities) trong game: 
    // bao gồm người chơi, quái vật, NPC, vật thể chuyển động, v.v.
    public class Entity {
        
        // Tọa độ thực của entity trong "thế giới" (world map), không phải tọa độ trên màn hình
        public float worldX, worldY;

        // Tốc độ di chuyển của entity (đơn vị: pixel/frame hoặc pixel/tick)
        public float speed;

        // Các sprite (hình ảnh) dùng để mô phỏng chuyển động theo từng hướng
        public BufferedImage up1, up2, up3;      // 3 frame chuyển động khi đi lên
        public BufferedImage left1, left2, left3; // 3 frame khi đi sang trái
        public BufferedImage down1, down2, down3; // 3 frame khi đi xuống
        public BufferedImage right1, right2, right3; // 3 frame khi đi sang phải

        // Hướng di chuyển hiện tại của entity: "up", "down", "left", "right"
        public String direction;

        // Bộ đếm và số thứ tự khung hình (sprite animation)
        public int spriteCounter = 0; // Đếm số frame trôi qua để chuyển sang sprite tiếp theo
        public int spriteNum = 1;     // Xác định frame hiện tại đang hiển thị (1, 2, hoặc 3)

        // Vùng va chạm (collision box) của entity tính theo pixel (tọa độ tương đối trong tile)
        public Point solidPoint; // Điểm góc trên trái của vùng va chạm
        public int solidPointDefaultX, solidPointDefaultY; // Dùng để reset vị trí khi cần

        // Biến kiểm soát trạng thái va chạm (true nếu có vật cản)
        public boolean collisionOn = false;
    }

Player.java

    package entity;

    import java.awt.Graphics2D;
    import java.awt.Point;
    import java.awt.geom.AffineTransform;
    import java.awt.image.BufferedImage;
    import java.io.IOException;
    import javax.imageio.ImageIO;
    import main.GamePanel;
    import main.KeyHandler;

    public class Player extends Entity {
        GamePanel gp; // Tham chiếu tới GamePanel chính (để truy cập bản đồ, đối tượng, âm thanh, UI, v.v.)
        KeyHandler keyH; // Bắt sự kiện bàn phím
        public int hasDiamond = 0; // Đếm số kim cương đã nhặt

        // Vị trí cố định của người chơi ở giữa màn hình (camera đứng yên, map di chuyển)
        public final double screenX;
        public final double screenY;
        
        // Khởi tạo player
        public Player(GamePanel gp, KeyHandler keyH) {
            this.gp = gp;
            this.keyH = keyH;
            setDefaultValues(); // Thiết lập vị trí, tốc độ, hướng mặc định
            getPlayerImage();   // Nạp hình ảnh cho các hướng di chuyển

            // Đặt nhân vật ở giữa màn hình (camera)
            screenX = gp.screenWidth / 2 - (up1.getWidth() / 4);
            screenY = gp.screenHeight / 2 - (up1.getHeight() / 4);

            // Thiết lập vùng va chạm (solid point) — vị trí tương đối dưới chân player
            solidPoint = new Point((int)(up1.getWidth() * 0.6 / 2), (int)(up1.getHeight() * 0.6));
            solidPointDefaultX = solidPoint.x;
            solidPointDefaultY = solidPoint.y;
        }

        // Thiết lập thông số mặc định của player
        public void setDefaultValues() {
            worldX = gp.tileSize * 19; // Vị trí X trong thế giới
            worldY = gp.tileSize * 19; // Vị trí Y trong thế giới
            speed = 2; // Tốc độ di chuyển
            direction = "down"; // Hướng mặc định
        }

        // Nạp toàn bộ hình ảnh sprite của player từ thư mục res
        public void getPlayerImage() {
            try {
                up1 = ImageIO.read(getClass().getResourceAsStream("/res/player/player_up1.png"));
                up2 = ImageIO.read(getClass().getResourceAsStream("/res/player/player_up2.png"));
                up3 = ImageIO.read(getClass().getResourceAsStream("/res/player/player_up3.png"));
                down1 = ImageIO.read(getClass().getResourceAsStream("/res/player/player_down1.png"));
                down2 = ImageIO.read(getClass().getResourceAsStream("/res/player/player_down2.png"));
                down3 = ImageIO.read(getClass().getResourceAsStream("/res/player/player_down3.png"));
                left1 = ImageIO.read(getClass().getResourceAsStream("/res/player/player_left1.png"));
                left2 = ImageIO.read(getClass().getResourceAsStream("/res/player/player_left2.png"));
                left3 = ImageIO.read(getClass().getResourceAsStream("/res/player/player_left3.png"));
                right1 = ImageIO.read(getClass().getResourceAsStream("/res/player/player_right1.png"));
                right2 = ImageIO.read(getClass().getResourceAsStream("/res/player/player_right2.png"));
                right3 = ImageIO.read(getClass().getResourceAsStream("/res/player/player_right3.png"));
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        
        // Hàm cập nhật mỗi frame (logic di chuyển, va chạm, hoạt ảnh)
        public void update() {
            if (keyH.isUpPressed || keyH.isDownPressed || keyH.isLeftPressed || keyH.isRightPressed) {
                double dx = 0, dy = 0;

                // Xác định hướng di chuyển dựa trên phím bấm
                if (keyH.isUpPressed) {
                    direction = "up";
                    dy = -speed;
                }
                if (keyH.isDownPressed) {
                    direction = "down";
                    dy = speed;
                }
                if (keyH.isLeftPressed) {
                    direction = "left";
                    dx = -speed;
                }
                if (keyH.isRightPressed) {
                    direction = "right";
                    dx = speed;
                }

                // Reset trạng thái va chạm
                collisionOn = false;

                // Kiểm tra va chạm với map và vật thể
                gp.cChecker.checkTile(this);
                int objIndex = gp.cChecker.checkObject(this, true);
                pickUpObj(objIndex);

                // Nếu không có va chạm → cập nhật vị trí
                if (!collisionOn) {
                    // Di chuyển chéo → giảm tốc độ để giữ tổng vận tốc đều
                    if (dx != 0 && dy != 0) {
                        dx /= 1.4142;
                        dy /= 1.4142;
                    }
                    worldX += dx;
                    worldY += dy;
                }

                // Xử lý chuyển động hoạt ảnh (3 frame luân phiên)
                spriteCounter++;
                if (spriteCounter > 6) {
                    spriteNum = spriteNum % 3 + 1;
                    spriteCounter = 0;
                }
            } else {
                spriteNum = 2; // Khi đứng yên, giữ sprite giữa
            }
        }

        int voiceSecond = 0;

        // Xử lý khi player chạm vào vật thể (kim cương, cửa,...)
        public void pickUpObj(int index) {
            if (index != 999) { // 999 = không có đối tượng
                String objName = gp.obj[index].name;
                voiceSecond = voiceSecond % 10 + 1;

                switch (objName) {
                    case "diamond":
                        hasDiamond++;
                        gp.obj[index] = null; // Xóa vật thể khỏi map
                        gp.ui.showMessage("You got a diamond!");
                        break;
                    case "door":
                        if (voiceSecond == 1) gp.playSound(1);
                        if (hasDiamond >= 3) gp.ui.showMessage("Comming soon bro!");
                        else gp.ui.showMessage("You need 3 diamonds!");
                        break;
                    default:
                        System.out.println("not diamond!");
                }
            }
        }
        
        // Vẽ player lên màn hình (theo hướng và frame hiện tại)
        public void draw(Graphics2D g2) {
            BufferedImage image = null;
            switch (direction) {
                case "up":
                    image = (spriteNum == 1) ? up1 : (spriteNum == 2 ? up3 : up2);
                    break;
                case "down":
                    image = (spriteNum == 1) ? down1 : (spriteNum == 2 ? down3 : down2);
                    break;
                case "left":
                    image = (spriteNum == 1) ? left1 : (spriteNum == 2 ? left3 : left2);
                    break;
                case "right":
                    image = (spriteNum == 1) ? right1 : (spriteNum == 2 ? right3 : right2);
                    break;
            }

            // Sử dụng AffineTransform để dịch chuyển và scale hình ảnh player
            AffineTransform at = new AffineTransform();
            at.translate(screenX, screenY);
            at.scale(0.6, 0.6); // Scale hình nhỏ lại 60% (ảnh gốc 96x96)
            g2.drawImage(image, at, null);
        }
    }

MapGenerator.java

    package tile;

    import java.util.Random;

    public class MapGenerator {
        // Kích thước bản đồ (100x100 ô)
        static final int SIZE = 100;

        // Các loại tile (ô bản đồ)
        static final int VOID = 0, DIRT = 1, GRASS = 2, WATER = 3, LAVA = 4, SAND = 5, BEDROCK = 6;

        // Ma trận lưu bản đồ
        static int[][] map = new int[SIZE][SIZE];

        // Đối tượng sinh ngẫu nhiên
        static Random rand = new Random();

        public static void main(String[] args) {
            generateMap();
            printMap(); // In ra map để kiểm tra
        }

        // Hàm chính sinh bản đồ
        public static void generateMap() {
            // 1️⃣ Khởi tạo toàn bộ bản đồ là ô trống (VOID)
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    map[i][j] = VOID;
                }
            }

            // 2️⃣ Tạo 4 vùng đất chính (40x40)
            int[][] lands = { {5, 5}, {55, 5}, {5, 55}, {55, 55} };
            for (int[] land : lands) {
                createLand(land[0], land[1]);
            }

            // 3️⃣ Nối các vùng đất bằng đường đất (DIRT) rộng 2 ô
            createRoad(45, 23, 54, 24); // Nối vùng 1 → 2
            createRoad(45, 73, 54, 74); // Nối vùng 3 → 4
            createRoad(23, 45, 24, 54); // Nối vùng 1 → 3
            createRoad(73, 45, 74, 54); // Nối vùng 2 → 4
        }

        // Tạo một vùng đất 40x40 tại vị trí (startX, startY)
        public static void createLand(int startX, int startY) {
            // Vẽ vùng đất
            for (int i = startX; i < startX + 40; i++) {
                for (int j = startY; j < startY + 40; j++) {
                    // Viền ngoài là đá (BEDROCK)
                    if (i == startX || i == startX + 39 || j == startY || j == startY + 39) {
                        map[i][j] = BEDROCK;
                    } else {
                        // Bên trong: 25% dirt, còn lại grass
                        map[i][j] = (rand.nextInt(4) == 0) ? DIRT : GRASS;
                    }
                }
            }

            // 4️⃣ Tạo ngẫu nhiên 1–3 hồ nước trong vùng
            int numLakes = rand.nextInt(3) + 1;
            for (int i = 0; i < numLakes; i++) {
                generateLake(startX, startY);
            }
        }

        // Sinh hồ nước trong vùng đất
        public static void generateLake(int startX, int startY) {
            // Kích thước ngẫu nhiên của hồ (2–9 ô)
            int lakeWidth = rand.nextInt(8) + 2;
            int lakeHeight = rand.nextInt(8) + 2;

            // Vị trí hồ nằm trong phạm vi vùng đất
            int lakeX = rand.nextInt(35 - lakeWidth) + startX + 2;
            int lakeY = rand.nextInt(35 - lakeHeight) + startY + 2;

            // 5️⃣ Đổ nước vào hồ
            for (int i = lakeX; i < lakeX + lakeWidth; i++) {
                for (int j = lakeY; j < lakeY + lakeHeight; j++) {
                    // 80% ô là nước → tạo hồ không đều
                    if (rand.nextInt(100) > 20) {
                        map[i][j] = WATER;
                    }
                }
            }

            // 6️⃣ Rải cát (SAND) xung quanh hồ, dày 1–2 ô
            for (int i = lakeX - 1; i <= lakeX + lakeWidth; i++) {
                for (int j = lakeY - 1; j <= lakeY + lakeHeight; j++) {
                    // Chỉ rải cát lên chỗ đang là cỏ (GRASS)
                    if (isValid(i, j) && map[i][j] == GRASS && rand.nextInt(100) < 90) {
                        map[i][j] = SAND;
                    }
                }
            }
        }

        // Kiểm tra ô có nằm trong bản đồ không
        public static boolean isValid(int x, int y) {
            return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
        }

        // Vẽ đường nối giữa hai vùng (hình chữ nhật)
        public static void createRoad(int x1, int y1, int x2, int y2) {
            for (int i = x1; i <= x2; i++) {
                for (int j = y1; j <= y2; j++) {
                    map[i][j] = DIRT;
                }
            }
        }

        // In bản đồ ra console (chỉ để test)
        public static void printMap() {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    System.out.print(map[i][j] + " ");
                }
                System.out.println();
            }
        }
    }

Tile.java

    package tile;

    import java.awt.image.BufferedImage;

    /**
    * Lớp Tile đại diện cho một ô (ô vuông hoặc hình chữ nhật)
    * trên bản đồ (map) trong game.
    * Mỗi Tile có thể có ảnh riêng, thuộc tính va chạm (collision)
    * và tỉ lệ hiển thị theo trục X/Y (đặc biệt khi tile không vuông).
    */
    public class Tile {

        // Ảnh hiển thị của tile (cỏ, đất, nước, đá, v.v.)
        public BufferedImage image;

        // Cho biết tile này có thể đi xuyên qua hay không
        // false → có thể đi qua, true → có va chạm (không thể đi qua)
        public boolean collision = false;

        // Hệ số tỉ lệ khi tile không phải là hình vuông
        // Dùng để chỉnh tỉ lệ hiển thị (ví dụ gạch dọc, nước chảy,...)
        public int normalX = 1, normalY = 1;

    }

Floattile.java

    package tile;

    import java.awt.Graphics2D;
    import java.io.BufferedReader;
    import java.io.IOException;
    import java.io.InputStream;
    import java.io.InputStreamReader;
    import javax.imageio.ImageIO;
    import main.GamePanel;

    /**
    * Lớp FloatTile dùng để quản lý các tile “nổi” trên mặt đất — ví dụ như:
    * tường, cây, đá, v.v... (những thứ có thể chắn người chơi hoặc che một phần thân).
    * 
    * Nó đọc dữ liệu từ file mapFloatTile.txt để xác định tile nào được vẽ
    * tại mỗi vị trí, đồng thời vẽ tile theo thứ tự sao cho player có thể đi 
    * "ẩn sau" các vật thể như cây hoặc tường.
    */
    public class FloatTile {
        GamePanel gp;                     // Tham chiếu đến GamePanel chính
        public Tile[] floatTile;          // Danh sách các tile nổi
        public int mapfloatTileNum[][];   // Ma trận lưu chỉ số tile nổi tại từng ô
        public int mapCollisionFTile[][]; // Ma trận va chạm của tile nổi

        // Định danh tile (giúp code dễ đọc hơn)
        public final int NULL = 0, BEDROCK = 1, TREE = 2, MOSS_ROCK_BLOCK = 3, ROCK_BLOCK = 4;

        // Constructor: khởi tạo các mảng, nạp ảnh và đọc map
        public FloatTile(GamePanel gp){
            this.gp = gp;
            floatTile = new Tile[50];  // Giới hạn tối đa 50 loại tile nổi
            getFloatTileImage();       // Nạp ảnh tile
            mapfloatTileNum = new int[gp.maxWorldCol][gp.maxWorldRow];
            mapCollisionFTile = new int[gp.maxWorldCol][gp.maxWorldRow];
            loadMap("/res/maps/mapFloatTile.txt");  // Đọc dữ liệu map từ file
        }

        /**
        * Nạp ảnh cho từng loại tile nổi (tường, cây, đá,...)
        * Đồng thời xác định tile nào có va chạm.
        */
        public void getFloatTileImage(){
            try{
                // NULL (ô trống)
                floatTile[NULL] = new Tile();
                floatTile[NULL].image = ImageIO.read(getClass().getResourceAsStream("/res/floattiles/null.png"));

                // BEDROCK (đá cứng – tường chắn)
                floatTile[BEDROCK] = new Tile();
                floatTile[BEDROCK].image = ImageIO.read(getClass().getResourceAsStream("/res/floattiles/bedrock_block_wall.png"));
                floatTile[BEDROCK].collision = true;
                floatTile[BEDROCK].normalX = 1;
                floatTile[BEDROCK].normalY = 2;   // Chiều cao gấp đôi 1 tile

                // TREE (cây to)
                floatTile[TREE] = new Tile();
                floatTile[TREE].image = ImageIO.read(getClass().getResourceAsStream("/res/floattiles/tree.png"));
                floatTile[TREE].collision = true;
                floatTile[TREE].normalX = 3;      // Rộng 3 tile
                floatTile[TREE].normalY = 3;      // Cao 3 tile

                // MOSS ROCK BLOCK (đá rêu)
                floatTile[MOSS_ROCK_BLOCK] = new Tile();
                floatTile[MOSS_ROCK_BLOCK].image = ImageIO.read(getClass().getResourceAsStream("/res/floattiles/moss_rock_block.png"));
                floatTile[MOSS_ROCK_BLOCK].collision = true;
                floatTile[MOSS_ROCK_BLOCK].normalX = 1;
                floatTile[MOSS_ROCK_BLOCK].normalY = 2;

                // ROCK BLOCK (đá thường)
                floatTile[ROCK_BLOCK] = new Tile();
                floatTile[ROCK_BLOCK].image = ImageIO.read(getClass().getResourceAsStream("/res/floattiles/rock_block.png"));
                floatTile[ROCK_BLOCK].collision = true;
                floatTile[ROCK_BLOCK].normalX = 1;
                floatTile[ROCK_BLOCK].normalY = 2;

            }catch(IOException e){
                e.printStackTrace();
            }
        }

        /**
        * Đọc file mapFloatTile.txt để gán loại tile nổi tương ứng cho từng ô.
        * Nếu tile có va chạm → đánh dấu trong mapCollisionFTile = 1
        */
        public void loadMap(String mapPath){
            try{
                InputStream is = getClass().getResourceAsStream(mapPath);
                BufferedReader br = new BufferedReader(new InputStreamReader(is));
                
                int col = 0, row = 0;

                while(col < gp.maxWorldCol && row < gp.maxWorldRow){
                    String line = br.readLine();
                    while(col < gp.maxWorldCol){
                        mapfloatTileNum[col][row] = Integer.parseInt((line.split(" "))[col]);
                        if(floatTile[mapfloatTileNum[col][row]].collision == true){
                            mapCollisionFTile[col][row] = 1;
                        }
                        col++;
                    }
                    row++;
                    col = 0;
                }

                br.close();
            } catch (Exception e){
                e.printStackTrace();
            }
        }

        int k = 0; // Biến dùng để điều khiển animation
        public void draw(Graphics2D g2) {

            // Giới hạn phạm vi vẽ trong khu vực xung quanh player để tối ưu FPS
            int worldLeftX = (int)(gp.player.worldX - gp.screenWidth / 2) / gp.tileSize - 1; 
            int worldRightX = (int)(gp.player.worldX + gp.screenWidth / 2) / gp.tileSize + 1;
            int worldTopY = (int)(gp.player.worldY - gp.screenHeight / 2) / gp.tileSize - 1;
            int worldBotY = (int)(gp.player.worldY + gp.screenHeight / 2) / gp.tileSize + 5;

            boolean isDrawEntity = false; // Đánh dấu xem player đã được vẽ chưa

            k = k % 60 + 1; // Bộ đếm animation (vòng lặp 1–60)

            // Duyệt qua từng ô tile trong khu vực hiển thị
            for(int j = worldTopY; j <= worldBotY; ++j){
                for(int i = worldLeftX; i <= worldRightX; ++i){

                    // Tính vị trí tile trên màn hình (theo tọa độ camera)
                    double screenX = i * gp.tileSize - gp.player.worldX + gp.player.screenX;
                    double screenY = j * gp.tileSize - gp.player.worldY + gp.player.screenY;

                    // Đảm bảo nằm trong giới hạn bản đồ
                    if(i >= 0 && j >= 0 && i < gp.maxWorldCol && j < gp.maxWorldRow){

                        int tileNum = mapfloatTileNum[i][j];

                        // Animation cho tile nước (7–12)
                        if(tileNum >= 7 && tileNum <= 12){
                            if((k + 1) % 10 == 0){
                                mapfloatTileNum[i][j]++;
                            }
                            if(mapfloatTileNum[i][j] == 13){
                                mapfloatTileNum[i][j] = 7;
                            }
                        }

                        // Animation cho lửa (16–33)
                        if(tileNum >= 16 && tileNum <= 33){
                            if((k + 1) % 2 == 0){
                                mapfloatTileNum[i][j]++;
                            }
                            if(mapfloatTileNum[i][j] == 34){
                                mapfloatTileNum[i][j] = 16;
                            }
                        }

                        // Nếu tile nằm *trên* người chơi → vẽ tile trước (dưới player)
                        if((j + 1) * gp.tileSize <= (gp.player.worldY + gp.player.solidPoint.y)){
                            if(tileNum != 0){
                                g2.drawImage(floatTile[tileNum].image, 
                                    (int)screenX - (floatTile[tileNum].normalX / 2) * gp.tileSize,
                                    (int)screenY - (floatTile[tileNum].normalY - 1) * gp.tileSize, 
                                    gp.tileSize * floatTile[tileNum].normalX,
                                    floatTile[tileNum].normalY * gp.tileSize, null);
                            }
                        } 

                        // Nếu tile nằm *sau* người chơi → vẽ player trước rồi tile sau
                        if((j + 1) * gp.tileSize > (gp.player.worldY + gp.player.solidPoint.y)){
                            if(!isDrawEntity){
                                gp.player.draw(g2); // Vẽ player xen giữa lớp tile
                                isDrawEntity = true;
                            }
                            if(tileNum != 0){
                                g2.drawImage(floatTile[tileNum].image, 
                                    (int)screenX - (floatTile[tileNum].normalX / 2) * gp.tileSize,
                                    (int)screenY - (floatTile[tileNum].normalY - 1) * gp.tileSize, 
                                    gp.tileSize * floatTile[tileNum].normalX,        
                                    floatTile[tileNum].normalY * gp.tileSize, null);
                            }
                        }
                    } 
                }
            }
        }
    }

TileManager.java

    package tile; // Khai báo package tile để nhóm các lớp liên quan đến tile (ô nền)

    import java.io.BufferedReader;
    import java.io.IOException;
    import java.io.InputStream;
    import java.io.InputStreamReader;
    import java.awt.Graphics2D;
    import javax.imageio.ImageIO;

    import main.GamePanel; // Import lớp GamePanel để truy cập kích thước bản đồ và thông tin người chơi

    public class TileManager { // Quản lý tất cả các tile trong bản đồ
        public final int VOID = 0, DIRT = 1, GRASS = 2, WATER = 3, LAVA = 4, SAND = 5, MAGMA = 6; // Các loại tile có ID riêng

        GamePanel gp; // Tham chiếu đến GamePanel để dùng thông tin kích thước và người chơi
        public Tile[] tile;    // Mảng lưu trữ các đối tượng Tile (hình ảnh + thuộc tính)
        public int mapTileNum[][]; // Mảng lưu số tile cho từng vị trí trong bản đồ
        public int mapCollisionTile[][]; // Mảng đánh dấu tile nào có va chạm

        public TileManager(GamePanel gp){ // Hàm khởi tạo TileManager
            this.gp = gp; // Gán tham chiếu đến GamePanel
            tile = new Tile[10]; // Tạo mảng tile có tối đa 10 loại
            mapTileNum = new int[gp.maxWorldCol][gp.maxWorldRow]; // Mảng chứa ID tile tại từng tọa độ (cột, hàng)
            mapCollisionTile = new int[gp.maxWorldCol][gp.maxWorldRow]; // Mảng lưu dữ liệu va chạm
            getTileImage(); // Nạp hình ảnh cho từng loại tile
            loadMap("/res/maps/mapTile.txt"); // Đọc file bản đồ và gán tile cho từng ô
        }

        public void getTileImage(){ // Hàm nạp hình ảnh các tile
            try{
                tile[VOID] = new Tile(); // Tạo tile trống
                tile[VOID].image = ImageIO.read(getClass().getResourceAsStream("/res/tiles/void.png")); // Ảnh ô trống

                tile[DIRT] = new Tile(); // Tile đất
                tile[DIRT].image = ImageIO.read(getClass().getResourceAsStream("/res/tiles/dirt.png"));

                tile[GRASS] = new Tile(); // Tile cỏ
                tile[GRASS].image = ImageIO.read(getClass().getResourceAsStream("/res/tiles/grass.png"));

                tile[WATER] = new Tile(); // Tile nước
                tile[WATER].image = ImageIO.read(getClass().getResourceAsStream("/res/tiles/water.png"));

                tile[LAVA] = new Tile(); // Tile dung nham
                tile[LAVA].image = ImageIO.read(getClass().getResourceAsStream("/res/tiles/lava.png"));

                tile[SAND] = new Tile(); // Tile cát
                tile[SAND].image = ImageIO.read(getClass().getResourceAsStream("/res/tiles/sand.png"));

                tile[MAGMA] = new Tile(); // Tile đá magma
                tile[MAGMA].image = ImageIO.read(getClass().getResourceAsStream("/res/tiles/magma.png"));

            }catch(IOException e){
                e.printStackTrace(); // In lỗi nếu không đọc được ảnh
            }
        }

        public void loadMap(String mapPath){ // Đọc file bản đồ tile
            try{
                InputStream is = getClass().getResourceAsStream(mapPath); // Mở file bản đồ
                BufferedReader br = new BufferedReader(new InputStreamReader(is)); // Dùng BufferedReader để đọc từng dòng
                
                int col = 0, row = 0; // Vị trí bắt đầu đọc map

                while(col < gp.maxWorldCol && row < gp.maxWorldRow){ // Lặp đến khi đọc hết map
                    String line = br.readLine(); // Đọc 1 dòng trong file map
                    while(col < gp.maxWorldCol){ // Duyệt qua từng cột của dòng
                        mapTileNum[col][row] = Integer.parseInt((line.split(" "))[col]); // Lấy số tile từ dòng
                        if(tile[mapTileNum[col][row]].collision == true){ // Nếu tile đó có va chạm
                            mapCollisionTile[col][row] = 1; // Ghi nhận va chạm
                        }
                        col++; // Sang cột tiếp theo
                    }
                    row++; // Sang hàng tiếp theo
                    col = 0; // Reset cột về 0
                }
                br.close(); // Đóng file sau khi đọc xong
            } catch (Exception e){
                e.printStackTrace(); // In lỗi nếu file map bị lỗi
            }
        }

        public void draw(Graphics2D g2){ // Vẽ tile ra màn hình

            // Tính giới hạn tile hiển thị trong vùng camera của người chơi
            int worldLeftX = (int)(gp.player.worldX - gp.screenWidth / 2) / gp.tileSize - 1; 
            int worldRightX = (int)(gp.player.worldX + gp.screenWidth / 2) / gp.tileSize + 1;
            int worldTopY = (int)(gp.player.worldY - gp.screenHeight / 2) / gp.tileSize - 1;
            int worldBotY = (int)(gp.player.worldY + gp.screenHeight / 2) / gp.tileSize + 1;

            for(int i = worldLeftX; i <= worldRightX; ++i){ // Duyệt theo cột
                for(int j = worldTopY; j <= worldBotY; ++j){ // Duyệt theo hàng
                    double screenX = i * gp.tileSize - gp.player.worldX + gp.player.screenX; // Tính vị trí tile trên màn hình (X)
                    double screenY = j * gp.tileSize - gp.player.worldY + gp.player.screenY; // Tính vị trí tile trên màn hình (Y)
                    if(i >= 0 && j >= 0 && i < gp.maxWorldCol && j < gp.maxWorldRow){ // Chỉ vẽ khi tile nằm trong bản đồ
                        int tileNum = mapTileNum[i][j]; // Lấy ID tile tại vị trí (i,j)
                        if(tileNum != 0){ // Không vẽ ô trống
                            g2.drawImage(tile[tileNum].image, (int)screenX, (int)screenY, gp.tileSize, gp.tileSize, null); // Vẽ tile
                        }
                    } 
                }
            }
        }
    }
