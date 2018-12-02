/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package laba3;

/**
 *
 * @author artem
 */
public class AffineTransform { //Перенос на вектор
    public static Matrix Translation(double x, double y, double z){
        Double T[] = {
                1.0, 0.0, 0.0, x,
                0.0, 1.0, 0.0, y,
                0.0, 0.0, 1.0, z,
                0.0, 0.0, 0.0, 1.0};
        return new Matrix(4, T);
    }
    
    public static Matrix Identity(){ // Identity() - тождественное АП;
        Double T[] = {
                1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                0.0, 0.0, 0.0, 1.0};
        return new Matrix(4, T);
    }
    
    public static Matrix RotationX(Double t){// Rotation(t) - поворот на угол t;
        Double T[] = {
                1.0, 0.0, 0.0, 0.0,
                0.0, Math.cos(t), -Math.sin(t), 0.0,
                0.0, Math.sin(t), Math.cos(t), 0.0,
                0.0, 0.0, 0.0, 1.0};
        return new Matrix(4, T);
    }
    
    public static Matrix RotationY(Double t){// Rotation(t) - поворот на угол t;
        Double T[] = {
                Math.cos(t), 0.0, Math.sin(t), 0.0,
                0.0, 1.0, 0.0, 0.0,
                -Math.sin(t), 0.0, Math.cos(t), 0.0,
                0.0, 0.0, 0.0, 1.0};
        return new Matrix(4, T);
    }
    
    public static Matrix RotationZ(Double t){// Rotation(t) - поворот на угол t;
        Double T[] = {
                Math.cos(t), -Math.sin(t), 0.0, 0.0,
                Math.sin(t), Math.cos(t), 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                0.0, 0.0, 0.0, 1.0};
        return new Matrix(4, T);
    }
    
    /*public static Matrix Rotation(Double c,Double s){// Rotation(c, s) - поворот на угол, косинус и синус которого пропорциональны величинам c и s;
        Double T[] = {
                1.0, 0.0, x,
                0.0, 1.0, y,
                0.0, 0.0, 1.0};
        return new Matrix(3, T);
    }*/
    
    public static Matrix Sw_v(){// Scaling(kx, ky) - масштабирование;
        Double T[] = {
                1.0, 0.0, 0.0, 0.0,
                0.0, -1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                0.0, 0.0, 0.0, 1.0};
        return new Matrix(4, T);
    }
    
    public static Double[][] Sv_p(){// Scaling(kx, ky) - масштабирование;
        Double T[][] = {
            {1.0, 0.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0},
            {0.0, 0.0, -10000.0, 0.0}};
        return T;
    }
    
    public static Matrix Scaling(Double kx,Double ky, Double kz){// Scaling(kx, ky) - масштабирование;
        Double T[] = {
                kx, 0.0, 0.0, 0.0,
                0.0, ky, 0.0, 0.0,
                0.0, 0.0, kz, 0.0,
                0.0, 0.0, 0.0, 1.0};
        return new Matrix(4, T);
    }
    
    public static Double[][] Sp(){// Rotation(t) - поворот на угол t;
        Double T[][] = {
            {1.0, 0.0, 0.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0, 0.0},
            {0.0, 0.0, 1.0, 0.0, 0.0},
            {0.0, 0.0, 0.0, 0.0, 1.0}};
        return T;
    }
    
    public static Matrix _3DRotationXY(Double t){// Rotation(t) - поворот на угол t;
        Double T[] = {
                Math.cos(t), -Math.sin(t), 0.0, 0.0, 0.0,
                Math.sin(t), Math.cos(t), 0.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 0.0, 1.0, 0.0,
                0.0, 0.0, 0.0, 0.0, 1.0};
        return new Matrix(5, T);
    }
    
    public static Double[][] _3DRotationXZ(Double t){// Rotation(t) - поворот на угол t;
        Double T[][] = {
            {1.0, 0.0, 0.0, 0.0, 0.0},
            {0.0, Math.cos(t), 0.0, Math.sin(t), 0.0},
            {0.0, 0.0, 1.0, 0.0, 0.0},
            {0.0, -Math.sin(t), 0.0, Math.cos(t), 0.0},
            {0.0, 0.0, 0.0, 0.0, 1.0}};
        return T;
    }
    
    public static Double[][] _3DRotationYZ(Double t){// Rotation(t) - поворот на угол t;
        Double T[][] = {
            {Math.cos(t), 0.0, 0.0, Math.sin(t), 0.0},
            {0.0, 1.0, 0.0, 0.0, 0.0},
            {0.0, 0.0, 1.0, 0.0, 0.0},
            {-Math.sin(t), 0.0, 0.0, Math.cos(t), 0.0},
            {0.0, 0.0, 0.0, 0.0, 1.0}};
        return T;
    }
    
    public static Double[][] _3DRotationYQZ(Double t){// Rotation(t) - поворот на угол t;
        Double T[][] = {
            {1.0, 0.0, 0.0, 0.0, 0.0},
            {0.0, Math.cos(t), -Math.sin(t), 0.0, 0.0},
            {0.0, Math.sin(t), Math.cos(t), 0.0, 0.0},
            {0.0, 0.0, 0.0, 1.0, 0.0},
            {0.0, 0.0, 0.0, 0.0, 1.0}};
        return T;
    }
    
//    public static Matrix Mapping1(){// Mapping (различные виды отражений) - по желанию, для создания матриц отражения можно использовать функцию Scaling.
//        Double T[] = {
//                -1.0, 0.0, 0.0,
//                0.0, 1.0, 0.0,
//                0.0, 0.0, 1.0};
//        return new Matrix(3, T);
//    }
//    
//    public static Matrix Mapping2(){// Mapping (различные виды отражений) - по желанию, для создания матриц отражения можно использовать функцию Scaling.
//        Double T[] = {
//                -1.0, 0.0, 0.0,
//                0.0, -1.0, 0.0,
//                0.0, 0.0, 1.0};
//        return new Matrix(3, T);
//    }
}
