/**
 * @author Manuel Gachs Ballegeer
 */
package Deepspace;

public interface SpaceFighter {
    public float fire();
    public float protection();
    public ShotResult recieveShot(float shot);
}
