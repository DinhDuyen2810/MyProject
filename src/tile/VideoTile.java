package tile;

import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

/**
 * Video Tile Animation - cắt frames từ water_still.png (16x512)
 * Mỗi frame là 16x16 pixel, cắt vertically từ trên xuống dưới
 * Tạo seamless looping animation
 */
public class VideoTile extends Tile {

    private List<BufferedImage> frames;
    private int currentFrameIndex = 0;
    private long lastFrameTime = 0;
    private int frameDelayMs = 100; // 100ms = 10 FPS

    // allow runtime adjustment of frame delay (ms)
    public void setFrameDelayMs(int ms) { if (ms < 1) ms = 1; this.frameDelayMs = ms; }
    public void multiplyFrameDelay(double factor) { if (factor <= 0) return; this.frameDelayMs = Math.max(1, (int)Math.round(this.frameDelayMs * factor)); }
    public int getFrameDelayMs() { return this.frameDelayMs; }
    private boolean isLoaded = false;
    private int totalFrames = 0;

    public VideoTile() {
        this.frames = new ArrayList<>();
    }

    /**
     * Load frames from an already-read spritesheet BufferedImage.
     * Frames are assumed to be square with width = spriteSheet.getWidth()
     * stacked vertically. Number of frames = height / width.
     * Each frame is scaled to outputSize x outputSize.
     */
    public void loadFromSpriteSheet(BufferedImage spriteSheet, int outputSize) {
        try {
            if (spriteSheet == null) {
                createFallbackFrames(outputSize);
                return;
            }

            int frameWidth = spriteSheet.getWidth();
            if (frameWidth <= 0) {
                createFallbackFrames(outputSize);
                return;
            }

            int sheetW = spriteSheet.getWidth();
            int sheetH = spriteSheet.getHeight();

            // Detect vertical or horizontal sprite strip where frames are square.
            // Vertical: frames stacked top->bottom => frameSize = sheetW, count = sheetH / sheetW
            // Horizontal: frames left->right => frameSize = sheetH, count = sheetW / sheetH
            int frameSize;
            int frameCount = 0;
            boolean vertical = false;

            if (sheetH >= sheetW && sheetW > 0 && sheetH % sheetW == 0) {
                vertical = true;
                frameSize = sheetW;
                frameCount = sheetH / sheetW;
            } else if (sheetW > 0 && sheetW % sheetH == 0) {
                vertical = false;
                frameSize = sheetH;
                frameCount = sheetW / sheetH;
            } else {
                // Not a regular square-frame strip; try to compute frames by integer division height/width
                if (sheetW > 0 && sheetH / sheetW >= 1) {
                    vertical = true;
                    frameSize = sheetW;
                    frameCount = sheetH / sheetW;
                } else {
                    createFallbackFrames(outputSize);
                    return;
                }
            }

            if (frameCount <= 0) {
                createFallbackFrames(outputSize);
                return;
            }

            for (int i = 0; i < frameCount; i++) {
                BufferedImage frameRaw;
                if (vertical) {
                    int frameY = i * frameSize;
                    int fh = Math.min(frameSize, spriteSheet.getHeight() - frameY);
                    frameRaw = spriteSheet.getSubimage(0, frameY, frameSize, fh);
                } else {
                    int frameX = i * frameSize;
                    int fw = Math.min(frameSize, spriteSheet.getWidth() - frameX);
                    frameRaw = spriteSheet.getSubimage(frameX, 0, fw, frameSize);
                }

                // Scale to outputSize
                BufferedImage frameScaled = new BufferedImage(outputSize, outputSize, BufferedImage.TYPE_INT_ARGB);
                Graphics2D g = frameScaled.createGraphics();
                g.setRenderingHint(java.awt.RenderingHints.KEY_INTERPOLATION,
                    java.awt.RenderingHints.VALUE_INTERPOLATION_NEAREST_NEIGHBOR);
                g.drawImage(frameRaw, 0, 0, outputSize, outputSize, null);
                g.dispose();

                frames.add(frameScaled);
            }

            totalFrames = frames.size();
            isLoaded = (totalFrames > 0);
            if (isLoaded) {
                this.image = frames.get(0);
                // Only log if multi-frame; single frame is treated as static image fallback
                if (totalFrames > 1) {
                    System.out.println("✓ Sprite animation loaded: " + totalFrames + " frames");
                }
            }

        } catch (Exception e) {
            System.err.println("✗ Lỗi load spriteSheet: " + e.getMessage());
            createFallbackFrames(outputSize);
        }
    }
    
    /**
     * Tạo fallback frames nếu water_still.png không có
     */
    private void createFallbackFrames(int tileSize) {
        try {
            // Tạo 8 frame blue gradient fallback
            for (int i = 0; i < 8; i++) {
                BufferedImage frame = new BufferedImage(tileSize, tileSize, BufferedImage.TYPE_INT_ARGB);
                Graphics2D g = frame.createGraphics();
                
                int blue = 150 + (i * 10);
                g.setColor(new java.awt.Color(30, Math.min(200, blue), 220, 255));
                g.fillRect(0, 0, tileSize, tileSize);
                
                // Wave pattern
                g.setColor(new java.awt.Color(100, 180, 255, 150));
                int offset = (i * 4) % tileSize;
                for (int y = offset; y < tileSize; y += 4) {
                    g.drawLine(0, y, tileSize, y);
                }
                g.dispose();
                
                frames.add(frame);
            }
            
            totalFrames = frames.size();
            isLoaded = true;
            System.out.println("⚠ Dùng fallback water animation (" + totalFrames + " frames)");
        } catch (Exception e) {
            System.err.println("✗ Fallback animation cũng lỗi");
            isLoaded = false;
        }
    }
    
    /**
     * Update animation frame dựa vào thời gian
     */
    public void update() {
        if (!isLoaded || totalFrames == 0) return;
        
        long currentTime = System.currentTimeMillis();
        
        if (lastFrameTime == 0) {
            lastFrameTime = currentTime;
            if (!frames.isEmpty()) {
                this.image = frames.get(0);
            }
            return;
        }
        
        long elapsed = currentTime - lastFrameTime;
        
        // Chuyển frame nếu đủ thời gian
        if (elapsed >= frameDelayMs) {
            currentFrameIndex = (currentFrameIndex + 1) % totalFrames;
            lastFrameTime = currentTime;
            
            if (currentFrameIndex < frames.size()) {
                this.image = frames.get(currentFrameIndex);
            }
        }
    }
    
    public boolean isLoaded() {
        return isLoaded;
    }
    
    public int getTotalFrames() {
        return totalFrames;
    }
    
    public int getCurrentFrameIndex() {
        return currentFrameIndex;
    }

    /**
     * Return current frame image (may be null until loaded)
     */
    public BufferedImage getCurrentFrameImage() {
        if (!isLoaded || frames.isEmpty()) return null;
        return frames.get(currentFrameIndex);
    }

    /**
     * Factory: create VideoTile from already-read spritesheet image.
     */
    public static VideoTile fromSpriteSheet(BufferedImage spriteSheet, int outputSize) {
        VideoTile vt = new VideoTile();
        vt.loadFromSpriteSheet(spriteSheet, outputSize);
        return vt;
    }

    /**
     * Create VideoTile from a list of already-extracted frames (may be rectangular).
     * Each BufferedImage in framesRaw will be scaled to `outputW` x `outputH`.
     */
    public static VideoTile fromFrames(java.util.List<BufferedImage> framesRaw, int outputW, int outputH) {
        VideoTile vt = new VideoTile();
        try {
            if (framesRaw == null || framesRaw.isEmpty()) return vt;

            for (BufferedImage frameRaw : framesRaw) {
                if (frameRaw == null) continue;
                BufferedImage frameScaled = new BufferedImage(outputW, outputH, BufferedImage.TYPE_INT_ARGB);
                Graphics2D g = frameScaled.createGraphics();
                g.setRenderingHint(java.awt.RenderingHints.KEY_INTERPOLATION,
                    java.awt.RenderingHints.VALUE_INTERPOLATION_NEAREST_NEIGHBOR);
                g.drawImage(frameRaw, 0, 0, outputW, outputH, null);
                g.dispose();
                vt.frames.add(frameScaled);
            }

            vt.totalFrames = vt.frames.size();
            vt.isLoaded = (vt.totalFrames > 0);
            if (vt.isLoaded) vt.image = vt.frames.get(0);
            System.out.println("✓ Sprite animation (from frames) loaded: " + vt.totalFrames + " frames");
        } catch (Exception e) {
            System.err.println("✗ Lỗi tạo animation từ frames: " + e.getMessage());
        }
        return vt;
    }

    /**
     * Convenience: load directly from resource path on classpath.
     */
    public static VideoTile fromResource(String resourcePath, int outputSize) {
        try (InputStream is = VideoTile.class.getResourceAsStream(resourcePath)) {
            if (is == null) return null;
            BufferedImage sprite = javax.imageio.ImageIO.read(is);
            if (sprite == null) return null;
            return fromSpriteSheet(sprite, outputSize);
        } catch (Exception e) {
            return null;
        }
    }
}
