package cn.Down;

import java.io.IOException;
import java.io.InputStream;
import java.io.RandomAccessFile;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * Created by donal on 2017/2/22.
 */

/**
 * 1.得到文件大小
 * 2.创建线程
 * 3.分配给若干个线程(写的位置，文件大小)
 *
 */
public class Test implements Runnable{

    private int id;
    private int startPoint;
    private int partFileSize;
    public Test(int id, int startPoint, int partFileSize){
        this.id = id;
        this.startPoint = startPoint;
        this.partFileSize = partFileSize;
    }

    @Override
    public void run(){
        try(
            RandomAccessFile randomAccessFile = new RandomAccessFile("yyf.png", "rw");
        )
        {
            URL url = new URL("http://101.95.48.97:8005/res/upload/interface/apptutorials/manualstypeico/6f83ce8f-0da5-49b3-bac8-fd5fc67d2725.png");
            HttpURLConnection connection = (HttpURLConnection)url.openConnection();
            connection.setConnectTimeout(8000);
            connection.setRequestMethod("GET");
            //防止屏蔽程序抓取而返回403错误
            connection.setRequestProperty("User-Agent", "Mozilla/4.0 (compatible; MSIE 5.0; Windows NT; DigExt)");
            connection.setRequestProperty("Accept",
                "image/gif, image/jpeg, image/pjpeg, image/pjpeg, "
                    + "application/x-shockwave-flash, application/xaml+xml, "
                    + "application/vnd.ms-xpsdocument, application/x-ms-xbap, "
                    + "application/x-ms-application, application/vnd.ms-excel, "
                    + "application/vnd.ms-powerpoint, application/msword, */*");
            connection.setRequestProperty("Accept-Language", "zh-CN");
            connection.setRequestProperty("Charset", "UTF-8");
            InputStream inputStream = connection.getInputStream();
            inputStream.skip(this.startPoint);
            byte[] buffer = new byte[1024];
            int hasRead = 0;
            int length = 0;
            randomAccessFile.seek(this.startPoint);
            while((length < this.partFileSize) && (hasRead = inputStream.read(buffer)) > 0){
                randomAccessFile.write(buffer, 0, hasRead);
                length += hasRead;
            }
            System.out.println("#" + this.id + " 我完成喽！！！" );
        }
        catch(IOException e){
            e.printStackTrace();
        }

    }
    public static void main(String[] args) {
        try(
            RandomAccessFile raf = new RandomAccessFile("yyf.png", "rw")
        )
        {
            URL url = new URL("http://101.95.48.97:8005/res/upload/interface/apptutorials/manualstypeico/6f83ce8f-0da5-49b3-bac8-fd5fc67d2725.png");
            HttpURLConnection connection = (HttpURLConnection)url.openConnection();
            connection.setConnectTimeout(8000);
            connection.setRequestMethod("GET");
            //防止屏蔽程序抓取而返回403错误
            connection.setRequestProperty("User-Agent", "Mozilla/4.0 (compatible; MSIE 5.0; Windows NT; DigExt)");
            connection.setRequestProperty("Accept",
                "image/gif, image/jpeg, image/pjpeg, image/pjpeg, "
                    + "application/x-shockwave-flash, application/xaml+xml, "
                    + "application/vnd.ms-xpsdocument, application/x-ms-xbap, "
                    + "application/x-ms-application, application/vnd.ms-excel, "
                    + "application/vnd.ms-powerpoint, application/msword, */*");
            connection.setRequestProperty("Accept-Language", "zh-CN");
            connection.setRequestProperty("Charset", "UTF-8");
            int fileSize = connection.getContentLength();
            //这里假设是5个线程.
            int threadSize = fileSize / 5 + 1;  //为了保证全部下下来
            int startPos = 0;
            ExecutorService executorService = Executors.newFixedThreadPool(5);
            for (int i = 0; i < 5; ++i){
                executorService.execute(new Test(i, startPos, threadSize));
                startPos += threadSize;
            }


        }
        catch (IOException e){
            e.printStackTrace();
        }
    }
}
