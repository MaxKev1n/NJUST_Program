package com.javaee.javaee.bean;

public class Order {
    private String orderno;
    private String userno;
    private String commodityno;
    private int quantity;
    private String location;
    private String tel;

    public String getOrderno(){
        return this.orderno;
    }
    public void setOrderno(String orderno){
        this.orderno = orderno;
    }
    public String getUserno(){
        return this.userno;
    }
    public void setUserno(String userno){
        this.userno = userno;
    }
    public String getCommodityno(){
        return this.commodityno;
    }
    public void setCommodityno(String commodityno){
        this.commodityno = commodityno;
    }
    public int getQuantity(){
        return this.quantity;
    }
    public void setQuantity(int quantity){
        this.quantity = quantity;
    }
    public String getLocation(){
        return this.location;
    }
    public void setLocation(String location){
        this.location = location;
    }
    public String getTel(){
        return this.tel;
    }
    public void setTel(String tel){
        this.tel = tel;
    }

}
