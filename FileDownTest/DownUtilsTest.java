package cn.Down;

/**
 * Created by donal on 2017/2/23.
 */
public class DownUtilsTest {
    public static void main(String[] args) {
        DownUtils downUtils = new DownUtils("http://p1.gexing.com/G1/M00/C8/77/rBACJlYnjHzxEOY2AAC9B6vX98g105.jpg"
            , "ais.jpg",  5);
        downUtils.download();

        /*new Thread(new Runnable() {
            @Override
            public void run() {
                while(downUtils.getCompleteRate() <1 ){
                    System.out.println("已完成:" + downUtils.getCompleteRate());
                    try {
                        Thread.sleep(10);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }

                }
            }
        });*/
    }
}
