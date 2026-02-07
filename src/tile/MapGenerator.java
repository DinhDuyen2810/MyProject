package tile;

import java.util.Random;

public class MapGenerator {
    static final int SIZE = 100;
    static final int VOID = 0, DIRT = 1, GRASS = 2, WATER = 3, LAVA = 4, SAND = 5, BEDROCK = 6;
    static int[][] map = new int[SIZE][SIZE];
    static Random rand = new Random();

    public static void main(String[] args) {
        generateMap();
        printMap();  // In ra map để kiểm tra
    }

    public static void generateMap() {
        // 1. Đặt toàn bộ bản đồ thành VOID (0)
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                map[i][j] = VOID;
            }
        }

        // 2. Xác định vị trí bốn vùng đất 40x40
        int[][] lands = { {5, 5}, {55, 5}, {5, 55}, {55, 55} };
        for (int[] land : lands) {
            createLand(land[0], land[1]);
        }

        // 3. Tạo đường đi rộng 2 nối các vùng đất bằng dirt (1)
        createRoad(45, 23, 54, 24); // Nối vùng 1 -> 2
        createRoad(45, 73, 54, 74); // Nối vùng 3 -> 4
        createRoad(23, 45, 24, 54); // Nối vùng 1 -> 3
        createRoad(73, 45, 74, 54); // Nối vùng 2 -> 4
    }

    public static void createLand(int startX, int startY) {
        // Tạo vùng đất 40x40, bọc ngoài bằng foot-rock (6)
        for (int i = startX; i < startX + 40; i++) {
            for (int j = startY; j < startY + 40; j++) {
                if (i == startX || i == startX + 39 || j == startY || j == startY + 39) {
                    map[i][j] = BEDROCK; // Viền foot-rock
                } else {
                    // 25% là dirt, còn lại là grass (cỏ phân bố không đều)
                    map[i][j] = (rand.nextInt(4) == 0) ? DIRT : GRASS;
                }
            }
        }

        // Tạo từ 1-3 hồ nước ngẫu nhiên
        int numLakes = rand.nextInt(3) + 1; // 1 đến 3 hồ nước
        for (int i = 0; i < numLakes; i++) {
            generateLake(startX, startY);
        }
    }

    public static void generateLake(int startX, int startY) {
        int lakeWidth = rand.nextInt(8) + 2;  // Kích thước ngẫu nhiên từ 2 đến 9
        int lakeHeight = rand.nextInt(8) + 2;
        int lakeX = rand.nextInt(35 - lakeWidth) + startX + 2; // Giữ hồ trong vùng đất
        int lakeY = rand.nextInt(35 - lakeHeight) + startY + 2;

        // Tạo hồ nước
        for (int i = lakeX; i < lakeX + lakeWidth; i++) {
            for (int j = lakeY; j < lakeY + lakeHeight; j++) {
                if (rand.nextInt(100) > 20) { // 80% ô là nước để tạo hình dạng không đều
                    map[i][j] = WATER;
                }
            }
        }

        // Rải cát xung quanh nước (Độ rộng 1-2 ô, phủ 90% diện tích cạnh nước)
        for (int i = lakeX - 1; i <= lakeX + lakeWidth; i++) {
            for (int j = lakeY - 1; j <= lakeY + lakeHeight; j++) {
                if (isValid(i, j) && map[i][j] == GRASS && rand.nextInt(100) < 90) {
                    map[i][j] = SAND;
                }
            }
        }
    }

    public static boolean isValid(int x, int y) {
        return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
    }

    public static void createRoad(int x1, int y1, int x2, int y2) {
        for (int i = x1; i <= x2; i++) { 
            for (int j = y1; j <= y2; j++) { 
                map[i][j] = DIRT;
            }
        }
    }

    public static void printMap() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                System.out.print(map[i][j] + " ");
            }
            System.out.println();
        }
    }
}
