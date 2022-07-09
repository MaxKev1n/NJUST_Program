package com.javaee.javaee.controller;


import com.javaee.javaee.bean.Commodity;
import com.javaee.javaee.service.CommodityService;
import com.javaee.javaee.bean.Order;
import com.javaee.javaee.service.OrderService;
import com.javaee.javaee.bean.User;
import com.javaee.javaee.service.UserService;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.List;

/**
 * 控制层，导入service层
 */
@Controller
public class controller {
    @Resource
    private CommodityService commodityService;

    //查询全部
    @RequestMapping("/commoditymanage")
    public String commodityList(Model model){
        List<Commodity> commodities = commodityService.findAll();
        model.addAttribute("commodities",commodities);
        return "commoditymanage";
    }

    //新增数据
    @RequestMapping("/commodityadd")
    public String add_commodity(Commodity commodity){
        commodityService.add(commodity);
        return "redirect:/commoditymanage";
    }
    /*@RequestMapping("/useradd")
    public String add(){
        return "add";
    }*/

    //删除数据
    @RequestMapping("/commoditydelete/{commodityno}")
    public String delete_commodity(@PathVariable String commodityno, HttpServletResponse servletResponse) throws IOException {
        int count =commodityService.delete(commodityno);
        if(count==1){
            servletResponse.sendRedirect("/commoditylist");
        }
        return "error";
    }

    //根据id查找
    @GetMapping("/commodity/{commodityno}")
    public String updatePage_commodity(RedirectAttributes attr, @PathVariable String commodityno){
        attr.addAttribute("commodityno",commodityno);
        return "redirect:/commodity";
    }

    @RequestMapping("/commodity")
    public String commodity(Model model,String commodityno){
        Commodity commodity = commodityService.select(commodityno);
        model.addAttribute("commodity",commodity);
        return "/commodity";
    }

    //更新数据
    @PostMapping("/commodityupdate")
    public String updateCommodity_commodity(Model model,Commodity commodity,HttpServletRequest request){
        String commodityno = request.getParameter("commodityno");
        Commodity commodityById = commodityService.select(commodityno);
        commodityService.update(commodityById);
        System.out.println(commodityById);
        return "redirect:/commoditylist";
    }

    @Resource
    private UserService userService;

    //查询全部
    @RequestMapping("/userlist")
    public String userList(Model model){
        List<User> users = userService.findAll();
        model.addAttribute("users",users);
        return "index";
    }

    //新增数据
    @RequestMapping("/register")
    public String register(HttpServletRequest req, HttpServletResponse resp){
        String username = req.getParameter("userno");
        String password = req.getParameter("pwd");
        String userno = req.getParameter("userno");
        String receivetel = req.getParameter("receivetel");
        String receivelo = req.getParameter("receivelo");

        User user = new User();
        user.setUserno(userno);
        user.setPwd(password);
        user.setAuthority(1);
        user.setUsername(username);
        user.setReceivelo(receivelo);
        user.setReceivetel(receivetel);

        userService.add(user);
        return "/index";

    }

    //删除数据
    @RequestMapping("/userdelete/{userno}")
    public String delete_user(@PathVariable String userno, HttpServletResponse servletResponse) throws IOException {
        int count =userService.delete(userno);
        if(count==1){
            servletResponse.sendRedirect("/userlist");
        }
        return "error";
    }

    //根据id查找
    @GetMapping("/userupdatePage/{userno}")
    public String updatePage_user(Model model,@PathVariable String userno){
        User users = userService.select(userno);
        model.addAttribute("users",users);
        return "modifi";
    }

    //更新数据
    @PostMapping("/userupdate")
    public String updateUser_user(Model model,User user,HttpServletRequest request){
        String userno = request.getParameter("userno");
        User userById = userService.select(userno);
        userService.update(userById);
        System.out.println(userById);
        return "redirect:/userlist";
    }

    @RequestMapping("/logins.html")
    public String logins(){
        return "/logins";
    }

    @RequestMapping("/loginu.html")
    public String loginu(){
        return "/loginu";
    }

    @RequestMapping("/index.html")
    public String index(){
        return "/index";
    }

    @RequestMapping("/register.html")
    public String register(){
        return  "/register";
    }

    @RequestMapping("/logins")
    public String logins(HttpServletRequest req, HttpServletResponse resp){
        String userno = req.getParameter("userno");
        String password = req.getParameter("pwd");

        User user = new User();
        user.setUserno(userno);
        user.setPwd(password);
        user.setAuthority(2);

        int flag = userService.login(user);

        if(flag == 0){
            return "redirect:/logins.html";
        }else if(flag == 2){
            return "redirect:/logins.html";
        }else{
            return "redirect:/index.html";
        }
    }

    @RequestMapping("/loginu")
    public String loginu(HttpServletRequest req, HttpServletResponse resp){
        String userno = req.getParameter("userno");
        String password = req.getParameter("pwd");

        User user = new User();
        user.setUserno(userno);
        user.setPwd(password);
        user.setAuthority(1);

        int flag = userService.login(user);

        if(flag == 0){
            return "redirect:/loginu.html";
        }else if(flag == 2){
            return "redirect:/loginu.html";
        }else{
            return "redirect:/index.html";
        }
    }

    @Resource
    private OrderService orderService;

    //查询全部
    @RequestMapping("/ordermanage")
    public String orderList(Model model){
        List<Order> orders = orderService.findAll();
        model.addAttribute("orders",orders);
        return "ordermanage";
    }

    //新增数据
    @RequestMapping("/orderadd")
    public String add_order(Order order){
        orderService.add(order);
        return "redirect:/ordermanage";
    }
    /*@RequestMapping("/useradd")
    public String add(){
        return "add";
    }*/

    //删除数据
    @RequestMapping("/orderdelete/{orderno}")
    public String delete_order(@PathVariable String orderno, HttpServletResponse servletResponse) throws IOException {
        int count =orderService.delete(orderno);
        if(count==1){
            servletResponse.sendRedirect("/ordermanage");
        }
        return "error";
    }

    //根据id查找
    @GetMapping("/orderupdatePage/{orderno}")
    public String updatePage_order(Model model,@PathVariable String orderno){
        Order orders = orderService.select(orderno);
        model.addAttribute("orders",orders);
        return "modifi";
    }

    //更新数据
    @PostMapping("/orderupdate")
    public String updateOrder_order(Model model, Order order, HttpServletRequest request){
        String orderno = request.getParameter("orderno");
        Order orderById = orderService.select(orderno);
        orderService.update(orderById);
        return "redirect:/ordermanage";
    }

    @RequestMapping("/index")
    public String init(Model model){
        List<Commodity> commodities1 = commodityService.selectByType(1);
        List<Commodity> commodities2 = commodityService.selectByType(2);
        List<Commodity> commodities3 = commodityService.selectByType(3);
        model.addAttribute("commodities1", commodities1);
        model.addAttribute("commodities2", commodities2);
        model.addAttribute("commodities3", commodities3);
        return "index";
    }
}

