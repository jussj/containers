struct rb_tree {
    enum color_t {
        RED, BLACK
    };

    struct node {
        color_t color;
        node *parent, *left, *right;

        node(color_t color): color{color} {}
    };

    using node_ptr = node *;

    static node_ptr const _nil;

private:
    static node _nil_val;
};

rb_tree::node rb_tree::_nil_val = rb_tree::node(rb_tree::BLACK);
rb_tree::node* const rb_tree::_nil = &rb_tree::_nil_val;

struct it
{
    rb_tree::node_ptr ptr;

    void func() {
        if (ptr != rb_tree::_nil) {
        }
    }
};
