/**
 * @author Manuel Gachs Ballegeer
 */
package Deepspace;

/**
 * @brief Tipos de armas
 */
public enum WeaponType {
    LASER(2.0f),
    MISSILE(3.0f),
    PLASMA(4.0f);
    private float power;
    WeaponType(float powerValue) {power = powerValue;}
    float getPower() {return power;}
}