package com.javaee.javaee.bean;

public class Commodity {
    private String commodityno;
    private String commodityname;
    private float price;
    private int stock;
    private String details;
    private String pic;
    private int type;

    public String getCommodityno(){
        return this.commodityno;
    }
    public void setCommodityno(String commodityno){
        this.commodityno = commodityno;
    }
    public String getCommodityname(){
        return this.commodityname;
    }
    public void setCommodityname(String commodityname){
        this.commodityname = commodityname;
    }
    public float getPrice(){
        return this.price;
    }
    public void setPrice(float price){
        this.price = price;
    }
    public int getStock(){
        return this.stock;
    }
    public void setStock(int stock){
        this.stock = stock;
    }
    public String getDetails(){
        return this.details;
    }
    public void setDetails(String details){
        this.details = details;
    }
    public String getPic(){
        return this.pic;
    }
    public void setPic(String pic){
        this.pic = pic;
    }
    public int getType(){
        return this.type;
    }
    public void setType(int type){
        this.type = type;
    }
}
