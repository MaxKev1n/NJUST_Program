package com.javaee.javaee.bean;

public class User {
    private String userno;
    private String username;
    private String pwd;
    private int authority;
    private String receivetel;
    private String receivelo;

    public String getUserno(){
        return this.userno;
    }
    public void setUserno(String userno){
        this.userno = userno;
    }
    public String getUsername(){
        return this.username;
    }
    public void setUsername(String username){
        this.username = username;
    }
    public String getPwd(){
        return this.pwd;
    }
    public void setPwd(String pwd){
        this.pwd = pwd;
    }
    public int getAuthority(){
        return this.authority;
    }
    public void setAuthority(int authority){
        this.authority = authority;
    }
    public String getReceivetel(){
        return this.receivetel;
    }
    public void setReceivetel(String receivetel){
        this.receivetel = receivetel;
    }
    public String getReceivelo(){
        return this.receivelo;
    }
    public void setReceivelo(String receivelo){
        this.receivelo = receivelo;
    }

}
