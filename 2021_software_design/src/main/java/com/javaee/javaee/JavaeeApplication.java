package com.javaee.javaee;

import org.mybatis.spring.annotation.MapperScan;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
@MapperScan(value = "com.javaee.javaee.dao")
public class JavaeeApplication {

    public static void main(String[] args) {
        SpringApplication.run(JavaeeApplication.class, args);
    }

}
