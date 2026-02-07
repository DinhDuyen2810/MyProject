package main;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class KeyHandler implements KeyListener {

    public boolean isUpPressed, isDownPressed, isLeftPressed, isRightPressed;
    public boolean showDebug = false; // toggled by F3

    @Override
    public void keyTyped(KeyEvent e) {
    }

    @Override
    public void keyPressed(KeyEvent e) {
        
        int code = e.getKeyCode();
        switch (code) {
            case KeyEvent.VK_F3:
                // toggle debug display
                showDebug = !showDebug;
                break;
            case KeyEvent.VK_W: case KeyEvent.VK_UP:
                isUpPressed = true;
                break;
            case KeyEvent.VK_S: case KeyEvent.VK_DOWN:
                isDownPressed = true;
                break;
            case KeyEvent.VK_A: case KeyEvent.VK_LEFT:
                isLeftPressed = true;
                break;
            case KeyEvent.VK_D: case KeyEvent.VK_RIGHT:
                isRightPressed = true;
                break;
        }

    }

    @Override
    public void keyReleased(KeyEvent e) {
        
        int code = e.getKeyCode();
        switch (code) {
            case KeyEvent.VK_W: case KeyEvent.VK_UP:
                isUpPressed = false;
                break;
            case KeyEvent.VK_S: case KeyEvent.VK_DOWN:
                isDownPressed = false;
                break;
            case KeyEvent.VK_A: case KeyEvent.VK_LEFT:
                isLeftPressed = false;
                break;
            case KeyEvent.VK_D: case KeyEvent.VK_RIGHT:
                isRightPressed = false;
                break;
        }
    }
    
}
