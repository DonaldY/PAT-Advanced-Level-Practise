package cn.Down;

/**
 * Created by donal on 2017/2/21.
 */

import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 *  实现多线程下载文件，支持断点续传
 *
 *  1.多线程
 *  2.下载：IO流
 *  3.断点续传：RandomAccessFile
 *  4.下载：URL
 *
 *  step1: 实现文件下载
 *  (step1,2 同时实现代码封装、整洁)
 *  step2: 多线程下载
 *  step3: 实现断点续传
 *
 *  实现断点续传：
 *  1.查看是否有临时文件，
 *      若无：则表明是新任务或者已完成的任务
 *      若有：则是突然有异常，中断了下载
 *          创建临时文件，用于保存断点(开始和结束的点)
 *              1.若每个线程创建一个文件，每次写完一段就写入文件一次
 *              2.若共用一个文件，会考虑到并发情况。(/(ㄒoㄒ)/~~。还有很多要学)
 *
 *      一般都是退出程序调用设置断点，比如点击按钮退出
 *      所以这里只需要提供这个接口就可以了。
 */
public class DownUtils {

    private final long fileSize;
    private final int threadSize;
    private final String url;
    private final String fileName;
    private final String targetDir;
    private final ExecutorService executorService;

    public DownUtils(String url, String fileName, String targetDir, int threadSize){
        this.url = url;
        this.fileName = fileName;
        this.targetDir = targetDir;
        this.threadSize = threadSize;
        executorService = Executors.newFixedThreadPool(threadSize);
        fileSize = getConnection(url).getContentLength();
    }

    public DownUtils(String url,String fileName, int threadSize){
        this.url = url;
        this.fileName = fileName;
        this.threadSize = threadSize;
        this.targetDir = "";
        executorService = Executors.newFixedThreadPool(threadSize);
        fileSize = getConnection(url).getContentLength();
    }

    public DownUtils(String url, String fileName){
        this.url = url;
        this.fileName = fileName;
        this.targetDir = "";
        this.threadSize = 1;
        executorService = Executors.newFixedThreadPool(threadSize);
        fileSize = getConnection(url).getContentLength();
    }

    private void makeSureDir(){
        File targetDir = new File(this.targetDir);
        if(!targetDir.exists())
            targetDir.mkdir();
    }

    public String getFileName(){
        if (!"".equals(targetDir)){
            makeSureDir();
            return targetDir + File.separator + fileName;
        }
        return fileName;
    }

    private static HttpURLConnection getConnection(String urlPath) {
        try {
            URL url = new URL(urlPath);
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
            return connection;
        } catch (IOException e){
            e.printStackTrace();
            throw new RuntimeException(e);
        }
    }

    public long getFileSize(){
        return fileSize;
    }

    private File fileFactory(String fileName){
        return new File(fileName);
    }

    private boolean isFileExist(){
        File targetFile = fileFactory(getFileName());
        if (targetFile.exists() && targetFile.length() == fileSize){
            System.out.println("The file you want to download has existed!!");
            return true;
        }
        return false;
    }

    private void createThread(){
        long partFileSize = fileSize / threadSize + 1;
        int startPos = 0;
        for (int i = 0 ; i < threadSize; ++i){
            executorService.execute(new DownThread(i, startPos, partFileSize));
            startPos += partFileSize;
        }
        executorService.shutdown();
    }

    public void download(){
        if (isFileExist())
            return;
        createThread();
    }
    
    private class DownThread implements Runnable{

        private long threadId;
        private long startPos;
        private long endPos;
        private long partFileSize;

        public DownThread(int threadId, int startPos, long partFileSize){
            this.threadId = threadId;
            this.startPos = startPos;
            this.partFileSize = partFileSize;
        }

        public void writePartFile(){
            try (
                InputStream inputStream = getConnection(url).getInputStream();
                RandomAccessFile raf = new RandomAccessFile(getFileName(), "rw")
            )
            {
                byte[] buffer = new byte[1024];
                int hasRead;
                int length = 0;
                inputStream.skip(startPos);
                raf.seek(startPos);
                while((length < partFileSize) && (hasRead = inputStream.read(buffer)) > 0){
                    raf.write(buffer, 0, hasRead);
                    length += hasRead;
                }
            }
            catch (IOException e){
                e.printStackTrace();
            }
        }

        public void makeSureTempFileExist(String tempFileName){
            File tempFile = fileFactory(tempFileName);

        }

        @Override
        public void run(){
            System.out.println("#" + threadId + " is loading...");
            File tempFile = fileFactory(threadId + ".txt");
            //若文件存在
            if (tempFile.exists()){

                //读取里面内容
                try(
                    RandomAccessFile raf = new RandomAccessFile(threadId + ".txt", "rw");
                    )
                {
                    raf.seek(0);
                    startPos = raf.readLong();
                    raf.seek(8);
                    endPos = raf.readLong();

                }
                catch (IOException e){
                    e.printStackTrace();
                }
            }

            writePartFile();
            System.out.println("#" + threadId + " succeeded!");
        }
    }

}
