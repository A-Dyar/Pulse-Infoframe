namespace CaseStudy.Models
{
    public class CartViewModel
    {
        public int CartId { get; set; }
        public string ProductId { get; set; }
        public string ProductName { get; set; }
        public string Description { get; set; }
        public string UserId { get; set; }
        public string DateCreated { get; set; }
        public int QtySold { get; set; }
        public int QtyOrdered { get; set; }
        public int QtyOnBackOrder { get; set; }
        public decimal OrderAmount { get; set; }
        public decimal OrderTax { get; set; }
        public decimal MSRP { get; set; }
    }
}