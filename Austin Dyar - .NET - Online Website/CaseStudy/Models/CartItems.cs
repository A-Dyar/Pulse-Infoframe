using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
namespace CaseStudy.Models
{
    public class CartItems
    {
        [Key]
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        public int Id { get; set; }
        [StringLength(15)]
        public int QtyOrdered { get; set; }
        public int QtySold { get; set; }
        public int QtyBackOrdered { get; set; }
        [Column(TypeName = "money")]
        public decimal SellingPrice { get; set; }


        public string ProductId { get; set; }
        [ForeignKey("ProductId")]
        public Product Product { get; set; }


        [ForeignKey("CartId")]
        public Cart Cart { get; set; }
        public int CartId { get; set; }
    }
}