import org.omg.CORBA.NO_IMPLEMENT;
import sun.awt.windows.WPrinterJob;

import javax.swing.*;
import javax.swing.plaf.IconUIResource;
import java.awt.*;
import java.awt.event.InputEvent;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Random;
import java.util.Stack;

public class Main {

    public static void bucketSort(Integer[] a) {
        ArrayList<Integer>[] bucket = new ArrayList[a.length];
        int max = a[0];
        for (int i = 0; i < a.length; i++) {
            if (a[i] > max)
                max = a[i];
        }

        for (int i = 0; i < a.length; i++) {
            int index = a[i] * a.length / (max + 1);
            //bucket.insert(a[index])
            //if empty
            if (bucket[index] == null) {
                bucket[index] = new ArrayList<>();
                bucket[index].add(a[i]);
            } else {
                //not empty

                for (int j = 0; j < bucket[index].size(); j++) {
                    if (bucket[index].get(j) < a[i]) {
                        if (j == bucket[index].size() - 1) {
                            bucket[index].add(a[i]);
                            break;
                        }
                        continue;
                    } else {
                        bucket[index].add(j, a[i]);
                        break;
                    }
                }

            }

        }
//        //test:show bucket
//        for(int i = 0; i < a.length; i++){
//            if(bucket != null){
//                System.out.println(bucket[i]);
//            }
//        }

        int pivot = 0;
        for (int i = 0; i < bucket.length; i++) {
            if (bucket[i] != null) {
                for (int j = 0; j < bucket[i].size(); j++) {
                    a[pivot++] = bucket[i].get(j);
                }
            } else {
                continue;
            }
        }

    }

    public static class Node {
        Node next = null;
        int data;

        Node(int data) {
            this.data = data;
        }

        void appendToTail(int data) {
            Node p = this;
            Node end = new Node(data);
            while (p.next != null) {
                p = p.next;
            }
            p.next = end;
        }

    }

    public static void show(Integer[] a) {
        for (int i = 0; i < a.length; i++) {
            System.out.printf("%d ", a[i]);
        }
        System.out.println();


    }

    public static void show(Node head) {
        Node p = head;
        while (p != null) {
            System.out.printf("%d ", p.data);
            p = p.next;
        }
        System.out.println();
    }

    public static void removeRepeative(Node head) {
        HashSet<Integer> hs = new HashSet<>();
        Node p = head;
        Node pre = null;
        while (p != null) {
            if (hs.contains(p.data)) {
                pre.next = pre.next.next;
                p = pre.next;
            } else {
                hs.add(p.data);
                pre = p;
                p = p.next;
                continue;
            }
        }
    }

    public static int getRverseKth(Node head, int k) {
        int res;
        Node pre = head;
        Node p = head.next;
        int count = 0;
        while (p != null) {
            count++;
            p = p.next;
        }
        int time = count - k + 1;
        if (time < 0)
            res = -1;
        else {
            for (int i = 0; i < time; i++) {
                pre = pre.next;
            }

            res = pre.data;
        }

        return res;
    }

    public static Node getReverse(Node head) {
        if (head == null || head.next == null) {
            return head;
        }

        Node remainder = getReverse(head.next);
        head.next.next = head;
        head.next = null;
//            return head;
//        } else {
//            Node p = remainder;
//            while (p.next != null){
//                p = p.next;
//            }
//            p.next = head;
//            head.next = null;
//        }

        return remainder;


//        // 如果为空链表或者只有一个节点的链表则不需要处理
//        if (head == null || head.next == null) {
//            return head;
//        }
//
//        // 递归直到找到尾结点
//        Node newHead = getReverse(head.next);
//
//        // 尾节点反指
//        head.next.next = head;
//
//        // 当前节点指向null节点
//        head.next = null;
//
//        return newHead;
    }

    //    public static Node reverse(Node head){
//        Node p1 = head;
//        Node p2 = head.next;
//        p1.next = null;
//        while (p2 != null){
//            Node p3 = p2.next;
//            p2.next = p1;
//            p1 = p2;
//            p2 = p3;
//        }
//        return p1;
//    }
    public static boolean isLoop(Node head) {
        Node p1 = head;
        Node p2 = head;
        do {
            p1 = p1.next;
            p2 = p2.next.next;
            if (p1 == p2) {
                Node start = head;
                while (p1 != start) {
                    p1 = p1.next;
                    start = start.next;
                }

                System.out.println(start.data);

                return true;
            }
        } while (p2 != null);


        return false;
    }

    public static Node getMiddleAddOne(Node root) {
        Node p1 = root;
        Node p2 = root;
        while (p2 != null && p2.next != null) {
            p2 = p2.next.next;
            p1 = p1.next;
        }


        return p1;

    }

    public static boolean isParlindrome(Node root) {
        Stack<Node> stack = new Stack<>();
        Node midR = getMiddleAddOne(root);
        System.out.println(midR.data);
        Node p = root;
        while (p != null) {
            stack.add(p);
            p = p.next;
        }

        p = root;
        while (p != midR) {
            Node popOne = stack.pop();
//            System.out.println(popOne.data);
            if (popOne.data == p.data){
                p = p.next;
                continue;
            } else {
                return false;
            }
        }

        return true;
    }

    public static void append(Node root, int data) {
        Node p = root;

        while (p.next != null) {
            p = p.next;
        }
        p.next = new Node(data);
    }
    /*
        检测鼠标的位置，到左上角停止检测
     */
    public static void detectMousePosition(){
        while (true){
            PointerInfo pinfo = MouseInfo.getPointerInfo();
            Point p = pinfo.getLocation();
            int mx = (int) p.getX();
            int my = (int) p.getY();
            System.out.printf("%d %d\n",mx,my);
            if(mx == 0 && my == 0)
                break;
        }

    }

    public static void callOutWindow(String software){
        if(software.compareTo("wechat") == 0){
            //ctrl + alt + w to show the window
            robot.keyPress(17);
            robot.keyPress(18);
            robot.keyPress(87);
            robot.keyRelease(17);
            robot.keyRelease(18);
            robot.keyRelease(87);
            // full screen win + up
            robot.keyPress(524);
            robot.keyPress(38);
            robot.keyRelease(38);
            robot.keyRelease(524);

        }
    }

    /**
     *
     * @param pointX
     * @param pointY
     * @param key
     * @param mode mode 1 means chinese(combined with pinyin space) mode 2 is English one
     *
     */
    public static void goHereAndClickSearch(int pointX, int pointY, String key, int mode){//mode 1 Chinese mode 2 English
        moveMouseTo(pointX,pointY);
        mouseClick(0);
        char keys[] = key.toUpperCase().toCharArray();
        for(int i = 0; i < keys.length; i++){
            robot.keyPress((int)keys[i]);
            robot.keyRelease((int)keys[i]);
        }
        if(mode == 1){
            //key down space
            robot.keyPress(32);//空格
            robot.keyRelease(32);
            robot.delay(1000);
            robot.keyPress(10);//enter
            robot.keyRelease(10);
        }
        if(mode == 2){

        }

    }
    public static void moveMouseToObjAndClick(String key){
        //update by different environment
        if(key.compareTo("zuowei") == 0){
            moveMouseTo(769,1001);
            mouseClick(0);
        }
    }
    public static Robot robot;

    static {
        try {
            robot = new Robot();
        } catch (AWTException e) {
            e.printStackTrace();
        }
    }

    public static void moveMouseTo(int pointX, int pointY){
        robot.mouseMove(pointX,pointY);
        robot.mouseMove(pointX,pointY);
        robot.mouseMove(pointX,pointY);
        robot.mouseMove(pointX,pointY);
        robot.mouseMove(pointX,pointY);
        //make sure that the position is right.
    }
    public static void mouseClick(int key){
        if(key == 0){//left down and up
            robot.delay(500);
            robot.mousePress(InputEvent.BUTTON1_DOWN_MASK);
            robot.delay(500);
            robot.mouseRelease(InputEvent.BUTTON1_DOWN_MASK);
        }
        if(key == -1){//left key down
        robot.mousePress(InputEvent.BUTTON1_DOWN_MASK);
        }
        if(key == 1){//left key up
        robot.mouseRelease(InputEvent.BUTTON1_DOWN_MASK);
        }
    }

    public static void main(String[] args) throws AWTException {
//        detectMousePosition();
//        moveMouseTo(1776,16);
//        mouseClick(0);
//        robot.delay(1000);
//        moveMouseTo(207,1063);
//        mouseClick(0);
        callOutWindow("wechat");
        goHereAndClickSearch(138,41,"wqtsg",1);
        moveMouseToObjAndClick("zuowei");
//        detectMousePosition();
    }
}

