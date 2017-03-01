package cn.Down;

/**
 * Created by donal on 2017/2/21.
 */

import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

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
            throw new RuntimeException("get connection default.");
        }
    }

    public void download(){
        if (isFileExist())
            return;
        System.out.println(url + "    is ready to download.----------");
        createThread();
    }

    private boolean isFileExist(){
        File targetFile = fileFactory(getFileName());
        if (targetFile.exists() && targetFile.length() == fileSize){
            System.out.println("The file you want to download has existed!!");
            return true;
        }
        return false;
    }

    private File fileFactory(String fileName){
        return new File(fileName);
    }

    public String getFileName(){
        if (!"".equals(targetDir)){
            makeSureDir();
            return targetDir + File.separator + fileName;
        }
        return fileName;
    }

    private void makeSureDir(){
        File targetDir = new File(this.targetDir);
        if(!targetDir.exists())
            targetDir.mkdir();
    }

    private void createThread(){
        long partFileSize = fileSize / threadSize + 1;
        long startPos = 0;
        for (int i = 0 ; i < threadSize; ++i){
            executorService.execute(new DownThread(i, startPos, partFileSize));
            startPos += partFileSize;
        }
        executorService.shutdown();
    }
    
    private class DownThread implements Runnable{

        private long threadId;
        private long startPos;
        private long endPos;
        private long partFileSize;
        private final String tempFileName;
        private transient File tempFile;

        public DownThread(int threadId, long startPos,  long partFileSize) {
            this.threadId = threadId;
            this.startPos = startPos;
            this.partFileSize = partFileSize;
            endPos = partFileSize + startPos;
            tempFileName = "temp" + threadId + ".txt";
        }

        @Override
        public void run(){
            System.out.println("#" + threadId + "---Thread is loading...");
            makeSureTempFileExist();
            writePartFile();
            System.out.println("#" + threadId + "---Thread succeeded!");
        }

        public void makeSureTempFileExist() {
            tempFile = new File(tempFileName);
            if (tempFile.exists()){
                readTempFile();
            }else {
                createTempFile();
            }
        }

        private void readTempFile(){
            try(
                RandomAccessFile raf = new RandomAccessFile(tempFileName, "rw")
            )
            {
                raf.seek(0);
                startPos = raf.readLong();
                raf.seek(8);
                endPos = raf.readLong();
                partFileSize = endPos - startPos;
            }
            catch (IOException e){
                throw new RuntimeException("read from temp file default.");
            }
        }

        private void createTempFile() {
            try {
                tempFile = File.createTempFile(tempFileName, null);
            } catch (IOException e) {
                throw new RuntimeException("create new file default.");
            }
        }

        public void writePartFile(){
            try (
                InputStream inputStream = getConnection(url).getInputStream();
                RandomAccessFile raf = new RandomAccessFile(getFileName(), "rw")
            )
            {
                byte[] buffer = new byte[1024];
                int hasRead;
                inputStream.skip(startPos);
                raf.seek(startPos);
                int length = 0;
                while((length < partFileSize) && (hasRead = inputStream.read(buffer)) > 0){
                    raf.write(buffer, 0, hasRead);
                    startPos += hasRead;
                }
                tempFile.deleteOnExit();
            }
            catch (IOException e){
                throw new RuntimeException("write part file default.");
            }
        }

        private void setBreakPoint(){
            try(
                RandomAccessFile raf = new RandomAccessFile(tempFileName, "rw")
                )
            {
                raf.writeLong(startPos);
                raf.writeLong(endPos);
            }
            catch (IOException e){
                e.printStackTrace();
                throw new RuntimeException("set break-point default.");
            }
        }

    }

}
