import "./Panel.css";
import React from "react";

interface PanelProps extends React.HTMLAttributes<HTMLDivElement> {
    children: React.ReactNode;
    className?: string;
}

export const Panel: React.FC<PanelProps> = ({ children, className = "", ...props }) => {
    return (
        <div className={`panel ${className}`} {...props}>
            {children}
        </div>
    );
};
