

/**
 * Created by donal on 2017/2/23.
 */
public class DownUtilsTest {
    public static void main(String[] args) {
        DownUtils downUtils = new DownUtils("https://gss0.baidu.com/-Po3dSag_xI4khGko9WTAnF6hhy/zhidao/pic/item/d1a20cf431adcbef25b551dfaaaf2edda2cc9f61.jpg"
            , "ais2.jpg",  5);
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
