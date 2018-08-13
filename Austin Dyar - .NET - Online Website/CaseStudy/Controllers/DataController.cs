using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using CaseStudy.Models;

namespace CaseStudy.Controllers
{
    public class DataController : Controller
    {
        AppDbContext _ctx;
        public DataController(AppDbContext context)
        {
            _ctx = context;
        }
        public IActionResult Index()
        {
            DataUtility util = new DataUtility(_ctx);
            string msg = "";
            var json = System.IO.File.ReadAllText(@"D:\\Semester 4 Folder\\INFO-3067 ASP.NET\\CaseStudy\\JSON\\Data.json");
            try
            {
                msg = (util.loadInformationFromFileToDb(json)) ? "tables loaded" : "problem loading tables";
            }
            catch (Exception ex)
            {
                msg = ex.Message;
            }
            ViewData["msg"] = msg;
            return View();
        }
    }
}